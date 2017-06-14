# Description
The gdsFileParser verifies GDSII files.  The parser mechanism exposes GDSII LEF data with callback functionality.

# Limitations
This library only parses, at the lowest level, the information contained in the GDSII files.  It does not provide an API to store this data in any persistent manner.  This is where the programmer must add their implementation on top of this library to make the data useful.

# Get Involved
If you or your company would like to participate in this project, please email us at support@eddrs.com.  If you want to do simple code or documentation fixes but do not want to be a participating party, please take a look at these instructions on how to create a new pull request https://help.github.com/articles/creating-a-pull-request/.

If you would like to ensure that this library covers a particular file or coverage of data in a file, please email us a test case file at support@eddrs.com or check it into the testData directory by following these instructions: https://help.github.com/articles/creating-a-pull-request/.  Please do not check-in any data that you don't want shared with the world.  We do not take any responsibility for design data that is part of this repository.

# The Test Data
Make sure you pull down this repository using the recursive flag.  This will supply more test data.
```sh
git clone --recursive https://github.com/EDDRSoftware/gdsFileParser
```

# Additional Notes
Calma-GDSII to Layout

Array => Instances

Boundary element => Polygon, Rectangle, Circle, Hole

Box element => Rectangle

Element => Text

Node => None

None => Pin

Path element => Path, Wire, Trace

Plex => None

Sref element => Instance

Structure element => Design

