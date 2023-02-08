# binary_fuzzer
i write a mini binary fuzer on c++ for fuzzing with input file with radamsa fuzzer
First of all, install radamsa and unpack the input.tar.xz file, to do this, write:

    git clone https://gitlab.com/akihe/radamsa && cd radamsa && make && cd .. && tar -xf input.tar.xz
For using write this command:

    ./bin_fuzz <target_elf_binary> <target_input_txt_file>
