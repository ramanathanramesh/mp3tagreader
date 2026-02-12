# mp3tagreader
MP3 Tag Reader is a C-based project that reads and edits ID3 metadata in MP3 files. It extracts details like Title, Artist, Album, Year, Genre, and Comment by parsing the ID3 header and frames. This project improved my understanding of file handling, binary data processing, and structured formats in C.


🎵 MP3 Tag Reader (C)
* About This Project

This is a simple C project where I built an MP3 Tag Reader to understand how MP3 files store song information internally.

MP3 files contain metadata called ID3 tags, which store details like Title, Artist, Album, Year, Genre, and Comments. In this project, I implemented functionality to read and edit these tags without damaging the actual audio data.

The program reads the ID3v2 header, calculates the tag size using sync-safe integer conversion, and parses each metadata frame carefully. Since the COMM (Comment) frame has a different internal structure, I handled it separately in both viewing and editing.

* What This Project Taught Me

How binary files are structured

How to work with file pointers (fseek, ftell)

How to safely modify data inside an existing file

Real-world use of C for low-level data processing

*Why I Built This

I wanted hands-on experience with structured file formats and binary parsing. This project helped me move beyond basic C programs and understand how real applications handle metadata internally
