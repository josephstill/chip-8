<articla>
  <header>
    <h1>Chip-8 Emulation</h1>
    <p>This is an exploration of chip-8 and hardware emulation. The goal of this project is to disassemble a chip 8 ROM and begin to understand the instruction set within. The next step will be to run the ROM on an emulator. Through this project I hope to learn a good bit about how hardware emulation works as well as become more comfortable with byte code and assembly language.</p>
  </header>
  <p> The following information will provide details in building and running the emulator as well as lessons learned and a summary of my experience with this project. I will also provide links for the purpose of record keeping and quick reference.</p>
  <br>
  <header>
    <h2>Dependencies</h2>
  </header>
    <p>The following is a list of libraries that you will need to build and run the project.</p>
    <ul style="list-style-type:disc>
      <li>CMake 2.6 or Later</li>
    </ul>
  <br>
  <header>
    <h2>Development Environment</h2>
  </header>
    <p>The following is a profile of my development environment</p>
    <ul style="list-style-type:disc>
      <li>Kubuntu 14.4</li>
      <li>CMake 2.8.12.2</li>
      <li>Eclipse 3.8.1</li>
      <li>GCC 4.8.2</li>
      <li>GDB 7.7.1</li>
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
  <p>Information will be added as the feature develops</p>
  <header>
    <h3>Disassembly</h3>  
  </header>
  <p>Information will be added as the feature develops</p>  
  <header>
    <h3>Emulation</h3>
  </header>
  <p>Information will be added as the feature develops</p>  
  <br>
  <header>
    <h2>Notes</h2>
  </header>
  <br>
  <header>
    <h2>Lessons Learned</h2>
  </header>
  <br>
  <header>
    <h2>Links</h2>
  </header>
  <p>The following are links to the sources of information that I have used in working on this project</p>
    <ul style="list-style-type:disc>
      <li><a href="http://devernay.free.fr/hacks/chip8/C8TECH10.HTM">Cowgod's Chip-8 Technical Reference</a></li>
      <li><a href="http://www.multigesture.net/wp-content/uploads/mirror/goldroad/chip8_instruction_set.shtml">Another Chip-8 Reference</a></li>
      <li><a href="http://emulator101.com/">Emulator 101</a></li>
      <li><a href="https://en.wikipedia.org/wiki/CHIP-8">Wikipedia</a></li>
    </ul>
</article>