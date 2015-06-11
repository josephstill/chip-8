<articla>
  <header>
    <h1>Chip-8 Emulation</h1>
    <p>This is an exploration of chip-8 and hardware emulation. The goal of this project is to disassemble a chip 8 ROM and begin to understand the instruction set within. The next step will be to run the ROM on an emulator. Through this project I hope to learn a good bit about how hardware emulation works as well as become more comfortable with byte code and assembly language.</p>
  </header>
  <p> The following information will provide details in building and running the emulator as well as lessons learned and a summary of my experience with this project. I will also provide links for the purpose of record keeping and quick reference.</p>
  <header>
    <h2>Contents</h2>
  </header>
  <ul>
    <li><a href="#Dependencies">Dependencies</a></li>
  </ul>
  <br>
  <header>
    <a name="Dependencies"><h2>Dependencies</h2></a>
  </header>
    <p>The following is a list of libraries that you will need to build and run the project.</p>
    <ul style="list-style-type:disc">
      <li>CMake 2.6 or Later</li>
      <li>Qt (More info soon)</li>
    </ul>
  <br>
  <header>
    <h2>Development Environment</h2>
  </header>
    <p>The following is a profile of my development environment</p>
    <ul style="list-style-type:disc">
      <li>Kubuntu 14.4</li>
      <li>CMake 2.8.12.2</li>
      <li>Eclipse 3.8.1</li>
      <li>GCC 4.8.2</li>
      <li>gdb 7.7.1</li>
      <li>git 1.9.1</li>
    </ul>
    <br>
  <header>
    <h2>Building</h2>
  </header>
  <p>Once the dependencies are installed and the source is downloaded, the build.sh script in the root directory of the project tree should do the work for you. It will change to the build subdirectory and run CMake for you. The output will be a binary called chip-8 and will be located in the build directory along side other build artifacts.</p>
  <br>
  <header>
    <h2>Features</h2>
    <p>The following is information regarding the features of the emulator and disassembler.</p>
  </header>
  <header>
    <h3>Hex Dumps</h3>
  </header>
  <p>Running the hex dump feature will display the bytes found inside the ROM with address offsets for a reference point. Currently this feature is only available in the command line tool; however, if there is time, a GUI will be added for this feature. The purpose for including this extra feature was that I found it useful when investigating bugs in file parsing. The hex dump feature is activated with the -x flag and requires that -f be specified with a file path. The output looks like this:</p>
  <pre>
    <samp>
      joseph@Joseph-MacBookPro$ ./chip-8 -x -f ../roms/Fishie.ch8
      00000000 00e0 a220 6208 60f8 7008 6110 4020 120e
      00000010 d108 f21e 7108 4130 1208 1210 0000 0000 
      00000020 0000 0000 0018 3c3c 0000 0000 0000 0000 
      00000030 0000 0000 0000 0000 0000 0000 0000 0000 
      00000040 3e3f 3f3b 3938 3838 0000 80c1 e7ff 7e3c 
      00000050 001f fff9 c080 0303 0080 e0f0 7838 1c1c 
      00000060 3838 393b 3f3f 3e3c 78fc fecf 8703 0100 
      00000070 0000 0000 80e3 ff7f 1c38 3870 f0e0 c000 
      00000080 3c18 0000 0000 0000 0000 0000 0000 0000 
      00000090 0000 0000 0000 0000 0000 0000 0000 0000 
    </samp>
  </pre>
  <br>
  <p>The hex dump was the first feature that I implemented as I was trying to become more familiar with the opcodes. Upon inspection of the hex dump, there is plenty of non opcode grouping of bytes. Another interesting thing that stands out, is the value at <code>0x000e</code>. Remembering that space up to <code>0x0200</code> is reserved for the system, this line would be in memory at <code>0x020e</code>. The command <code>0x120e</code> is a jump to <code>0x020e</code> which is a jump to itself.</p>
  <header>
    <h3>Disassembly</h3>  
  </header>
  <p>Running the disassembly tool will provide you with assembly listings for the opcodes found withing the ROM file. Currently this feature is only available in the command line tool; however, it will be added to the GUI once it is implemented. The format of this output is linear from <code>0x0200</code> until the end of the program data. For each opcode, the data section will be parsed in two byte increments; However, there can be one byte sections of data in the ROM, meaning that it is not a requirement that an opcode start at an even offset within the file. Thus, raw data will be parsed in one byte increments. For the command line tool, the disassembly feature is activated using the -d flag and requires that -f be specified with a file path. The output looks like this:</p>
  <pre>
    <code>
      0x200          CLS
      0x202          LD I, 0x220
      0x204          LD V2, 0x08
      0x206          LD V0, 0xf8
      0x208 link_208 ADD V0, 0x08
      0x20a          LD V1, 0x10
      0x20c          SNE V0, 0x20
      0x20e link_20e JP link_20e
      0x210 link_210 DRW  V1, V0, 0x8
      0x212          ADD I, V2
      0x214          ADD V1, 0x08
      0x216          SNE V1, 0x30
      0x218          JP link_208
      0x21a          JP link_210
      0x21c          DATA 0x00
      ...
      0x240          DATA 0x3e
      0x241          DATA 0x3f
      0x242          DATA 0x3f
      0x243          DATA 0x3b
      0x244          DATA 0x39
      0x245          DATA 0x38
      0x246          DATA 0x38
      ...
      0x29f          DATA 0x00
    </code>
  </pre>
  <p>This particular output is for the ROM that produced the hex dump shown above. The assembly listings used are the ones found <a href="http://devernay.free.fr/hacks/chip8/C8TECH10.HTM">here</a>. I have also chosen to add labels to the jump commands instead of leaving the hex address as the argument. Also, from inspecting the above output it is more clear that the command at <code>0x20e</code> jumps to itself.</p>
  <p>From working with the disassembly, there are a few features that I would like to see implemented, should I have time. The most meaningful would be a way to make sense of the data sections that are found in the ROM file. It appears that these memory locations are the sprites that are drawn by the emulator; a graphical representation of these would be a nice feature and I intend on adding it should there be time. The second feature that I thing would be interesting is an assembler. I have included some groundwork for an assembler; however, it is outside of the scope of the current iteration of this project.</p>
  <header>
    <h3>Emulation</h3>
  </header>
  <p>Information will be added as the feature develops</p>
  <br>
  <header>
    <h2>Notes and Lessons Learned</h2>
    <p>From looking through some of the sample ROMs, it looks like the jumps may not always fall on an even number instruction. There is an example of this in Space Invaders, which starts with a jump to 0x225. It also appears that there is non instruction data inside some of the ROMs which will make linear parsing of instructions inaccurate. My search led me to a process called recursive decent which involves augmenting a linear disassembly by following links and branches. I will treat any left over information as data and have updated the disassembly output display it. Since I have seen some jumps to uneven address and addresses must be of even size, I am displaying the data in nibble intervals to ensure all of it is displayed.</p>
  </header>
  <br>
  <header>
    <h2>Links</h2>
  </header>
  <p>The following are links to the sources of information that I have used in working on this project</p>
    <ul style="list-style-type:disc">
      <li><a href="http://devernay.free.fr/hacks/chip8/C8TECH10.HTM">Cowgod's Chip-8 Technical Reference</a></li>
      <li><a href="http://www.multigesture.net/wp-content/uploads/mirror/goldroad/chip8_instruction_set.shtml">Another Chip-8 Reference</a></li>
      <li><a href="http://emulator101.com/">Emulator 101</a></li>
      <li><a href="http://www.pong-story.com/chip8/">David Winter's Chip-8 Emulation Page</a></li>
      <li><a href="https://en.wikipedia.org/wiki/CHIP-8">Wikipedia</a></li>
      <li><a href="http://resources.infosecinstitute.com/linear-sweep-vs-recursive-disassembling-algorithm/">Recursive Disassembly</a></li>
      <li><a href="http://neilscomputerblog.blogspot.com/2011/10/disassembly-algorithms.html">Disassembly Algorithms</a></li>
      <li><a href="http://reverseengineering.stackexchange.com/questions/2347/what-is-the-algorithm-used-in-recursive-traversal-disassembly">Stack Exchange</a></li>  
    </ul>
</article>