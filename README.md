This project has been started with the idea of translating CARMEN Log format to ROS messages after some struggling to find some program that did it, and the those found were not satisfying. Its main objective is to develop a ROS node capable of receiving other than CARMEN Log files to read and then translate this information to TOD msgs. To achieve this, the project relies on good software engineering and software pattern usage.

The next steps of this project are:

-Refactor the source code of the original CARMEN/ROS translator to allow an easy addition of different file readers;
-Add file readers of every type of recorded information files presented in radish database(those formats concerning only 2D laser scans and odometry readings for 2D SLAM, at the beginning) http://radish.sourceforge.net/
-Increasingly add new reading capabilities of different files for 2D SLAM and other objectives
