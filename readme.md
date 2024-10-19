# archive
this is a custom archive project aimed to archive and dearchive files from a binary file
# how to use
- archive: `./archive a name.archive file1 file2 ...`
- extract file by index: `./archive x name.archive 0 file0_output`
- extract everything into a directory: `./archive xa name.archive dir/`
- list files in the archive: `./archive l name.archive`
# instructions on how to build and run
- `git clone https://github.com/splexas/archive/`
- `cd archive`
- `make`
- `./archive`
