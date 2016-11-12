# videoFrames
Small project to get to know C++ opencv. It should create a database of screenshots obtained from avi files.

The main objective was to create a small script that allows the user to create a database of pictures from avi files.
It only takes one argument - the path to your folder with input videos.
There should be subdirectories with input avi files inside the main one. It saves one frame per two seconds (each 48th frame from the video).
Frames are saved to "frames" dir created by the script, ready to be used in machine learning algorithms :3
