/*
 * MIT License
 *
 * Copyright (c) 2017 EDDR Software, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Attribution: Thanks for Jim Buchanan for his description of the Calma format.
 *              http://www.buchanan1.net/stream_description.html
 */

/*
 * Changes:
 * 2017-01-01: First & Last Name: What you did.
 * 2017-06-10: Kevin Nesmith: Initial contribution.
 *
 */

#ifndef GDSCALMARECORDS_H_
#define GDSCALMARECORDS_H_

namespace gdsfp
{
    /*
     *  Record data type
     */
    enum RecordDataType {
        NO_DATA         = 0x00,
        BIT_ARRAY       = 0x01,
        INTEGER_2       = 0x02,
        INTEGER_4       = 0x03,
        REAL_4          = 0x04,
        REAL_8          = 0x05,
        ASCII_STRING    = 0x06
    };

    /*
     *  Record type                    Data type
     */
    enum RecordType {
        HEADER          = 0x00,     /* 0x02 INTEGER_2  Start of stream, contains version number of
                                       stream file.
                                       < v3.0  0x0000    0
                                         v3.0  0x0003    3
                                         v4.0  0x0004    4
                                         v5.0  0x0005    5
                                         v6.0  0x0258  600 */
        BGNLIB          = 0x01,   /* 0x02 INTEGER_2  Beginning of library, plus mod and access
                                       dates.
                                       Modification:
                                       year, month, day, hour, minute, second
                                       Last access:
                                       year, month, day, hour, minute, second */
        LIBNAME         = 0x02,   /* 0x06 STRING     The name of the library, supposedly following
                                       Calma DOS conventions. Using later tools,
                                       such as ISS LTL-100, it seems more flexible
                                       than that, but it won't allow any old thing
                                       you want. If memory serves, Calma DOS allowed
                                       6 characters in a file name, with a 2
                                       character extension. */
        UNITS           = 0x03,   /* 0x05 REAL_8     Size of db unit in user units, size of db
                                       unit in meters. To calculate the size of
                                       a user unit in meters, divide the second
                                       number by the first.*/
        ENDLIB          = 0x04,   /* 0x00 NO_DATA    End of the library. */
        BGNSTR          = 0x05,   /* 0x02 INTEGER_2  Begin structure, plus create and mod dates in
                                       the same format as the BGNLIB record. */
        STRNAME         = 0x06,   /* 0x06 STRING     Name of a structure. Up to 32 characters in
                                       GDSII, A-Z, a-z, 0-9, _, ?, and $ are all legal characters. */
        ENDSTR          = 0x07,   /* 0x00 NO_DATA    End of a structure. */
        BOUNDARY        = 0x08,   /* 0x00 NO_DATA    The beginning of a BOUNDARY element. */
        PATH            = 0x09,   /* 0x00 NO_DATA    The beginning of a PATH element. */
        SREF            = 0x0a,   /* 0x00 NO_DATA    The beginning of an SREF element. */
        AREF            = 0x0b,   /* 0x00 NO_DATA    The beginning of an AREF element. */
        TEXT            = 0x0c,   /* 0x00 NO_DATA    The beginning of a TEXT element. */
        LAYER           = 0x0d,   /* 0x02 INTEGER_2  Layer specification. On GDSII this could be
                                       0 to 63, LTL allows 0 to 255. Of course a
                                       3 byte integer allows up to 65535... */
        DATATYPE        = 0x0e,   /* 0x02 INTEGER_2  Datatype specification. On GDSII this could
                                       be 0 to 63, LTL allows 0 to 255. Of course a
                                       3 byte integer allows up to 65535... */
        WIDTH           = 0x0f,   /* 0x03 INTEGER_4  Width specification, negative means absolute
                                       In data base units. */
        XY              = 0x10,   /* 0x03 INTEGER_4  An array of XY coordinates. An array of
                                       coordinates in data base units.
                                       Path: 2 to 200 pairs in GDSII
                                       Boundary: 4 to 200 pairs in GDSII
                                       Text: Exactly 1 pair
                                       SREF: Exactly 1 pair
                                       AREF: Exactly 3 pairs
                                             1:  Array reference point
                                             2:  column_space*columns+reference_x
                                             3:  row_space*rows+reference_y
                                       Node: 1 to 50 pairs in GDSII
                                       Box:  Exactly 5 pairs */
        ENDEL           = 0x11,   /* 0x00 NO_DATA    The end of an element. */
        SNAME           = 0x12,   /* 0x06 STRING     The name of a referenced structure. */
        COLROW          = 0x13,   /* 0x02 INTEGER_2  Columns and rows for an AREF. Two 2 byte
                                       integers. The first is the number of columns.
                                       The second is the number of rows. In an AREF
                                       of course. Neither may exceed 32767 */
        TEXTNODE        = 0x14,   /* 0x00 NO_DATA    "Not currently used" per GDSII Stream Format
                                       Manual, v6.0. Would be the beginning of a
                                       TEXTNODE element if it were. */
        NODE            = 0x15,   /* 0x00 NO_DATA    The beginning of a NODE element. */
        TEXTTYPE        = 0x16,   /* 0x02 INTEGER_2  Texttype specification. On GDSII this could
                                       be 0 to 63, LTL allows 0 to 255. Of course a
                                       3 byte integer allows up to 65535... */
        PRESENTATION    = 0x17,   /* 0x01 BIT_ARRAY  Text origin and font specification.
                                       bits 15 to 0, l to r
                                       bits 0 and 1: 00 left, 01 center, 10 right
                                       bits 2 and 3: 00 top 01, middle, 10 bottom
                                       bits 4 and 5: 00 font 0, 01 font 1,
                                                 10 font 2, 11 font 3, */
        SPACING         = 0x18,   /* UNKNOWN    "Discontinued" per GDSII Stream Format
                                       Manual, v6.0. */
        STRING          = 0x19,   /* 0x06 STRING     Character string. Up to 512 char in GDSII */
        STRANS          = 0x1a,   /* 0x01 BIT_ARRAY  Bits 15 to 0, l to r
                                       15=refl, 2=absmag, 1=absangle, others
                                       reserved for future use. */
        MAG             = 0x1b,   /* 0x05 REAL_8     Magnification, 1 is the default if omitted. */
        ANGLE           = 0x1c,   /* 0x05 REAL_8     Angular rotation factor in ccw direction.
                                       If omitted, the default is 0. */
        UINTEGER        = 0x1d,   /* UNKNOWN    User integer, used only in V2.0, when
                                       instreamed, should be converted to property
                                       attribute 126. */
        USTRING         = 0x1e,   /* UNKNOWN    User string, used only in V2.0, when
                                       instreamed, should be converted to property
                                       attribute 127. */
        REFLIBS         = 0x1f,   /* 0x06 STRING     Names of the reference libraries. Starts with
                                       name of the first library and is followed by
                                       the second. There are 44 bytes in each, NULLS
                                       are used for padding, including filling in an
                                       entire unused field. */
        FONTS           = 0x20,   /* 0x06 STRING     Names of the textfont definition files. 4 44
                                       byte fields, padded with NULLS if a field is
                                       unused or less than 44 bytes. */
        PATHTYPE        = 0x21,   /* 0x02 INTEGER_2  Type of path ends.
                                       0: Square ended paths
                                       1: Round ended
                                       2: Square ended, extended 1/2 width
                                       4: Variable length extensions, CustomPlus
                                       The default is 0 */
        GENERATIONS     = 0x22,   /* 0x02 INTEGER_2  Number of deleted or backed up structures to
                                       retain. Seems a bit odd in an archive...
                                       From 2-99, default is 3. */
        ATTRTABLE       = 0x23,   /* 0x06 STRING     Name of the attribute definition file. Max
                                       size 44 bytes. */
        STYPTABLE       = 0x24,   /* 0x06 STRING     "Unreleased feature" per GDSII Stream Format
                                       Manual, v6.0. */
        STRTYPE         = 0x25,   /* 0x02 INTEGER_2  "Unreleased feature" per GDSII Stream Format
                                       Manual, v6.0 */
        ELFLAGS         = 0x26,   /* 0x01 BIT_ARRAY  Flags for template and exterior data.
                                       bits 15 to 0, l to r
                                       0=template, 1=external data, others unused */
        ELKEY           = 0x27,   /* 0x03 INTEGER_4  "Unreleased feature" per GDSII Stream Format
                                       Manual, v6.0. */
        LINKTYPE        = 0x28,   /* UNKNOWN    "Unreleased feature" per GDSII Stream Format
                                       Manual, v6.0. */
        LINKKEYS        = 0x29,   /* UNKNOWN    "Unreleased feature" per GDSII Stream Format
                                       Manual, v6.0. */
        NODETYPE        = 0x2a,   /* 0x02 INTEGER_2  Nodetype specification. On GDSII this could
                                       be 0 to 63, LTL allows 0 to 255. Of course a
                                       3 byte integer allows up to 65535... */
        PROPATTR        = 0x2b,   /* 0x02 INTEGER_2  Property number. */
        PROPVALUE       = 0x2c,   /* 0x06 STRING     Property value. On GDSII, 128 characters max,
                                       unless an SREF, AREF, or NODE, which may
                                       have 512 characters. */
        BOX             = 0x2d,   /* 0x00 NO_DATA    The beginning of a BOX element. */
        BOXTYPE         = 0x2e,   /* 0x02 INTEGER_2  Boxtype specification. On GDSII this could be
                                       0 to 63, LTL allows 0 to 255. Of course a
                                       3 byte integer allows up to 65535... */
        PLEX            = 0x2f,   /* 0x03 INTEGER_4  Plex number and plexhead flag. The least
                                       significant bit of the most significant byte
                                       is the plexhead flag. Because of this, you
                                       can "only" have 2^24 plex groups. Or is that
                                       2^24-1? I'm not sure if 0 is a valid plex
                                       group in a stream file. */
        BGNEXTN         = 0x30,   /* 0x03 INTEGER_4  Path extension beginning for pathtype 4 in
                                       CustomPlus. In database units, may be
                                       negative. */
        ENDEXTN         = 0x31,   /* 0x03 INTEGER_4  Path extension end for pathtype 4 in
                                       CustomPlus. In database units, may be
                                       negative. */
        TAPENUM         = 0x32,   /* 0x02 INTEGER_2  Tape number for multi-reel stream file. */
        TAPECODE        = 0x33,   /* 0x02 INTEGER_2  Tape code to verify that the reel is from the
                                       proper set. 12 bytes that are supposed to
                                       form a unique tape code. */
        STRCLASS        = 0x34,   /* 0x01 BIT_ARRAY  Calma use only. In stream files created by
                                       non-Calma programs, this should be missing or
                                       all field should be 0. */
        RESERVED        = 0x35,   /* 0x03 INTEGER_4  Used to be NUMTYPES per GDSII Stream Format
                                       Manual, v6.0. */
        FORMAT          = 0x36,   /* 0x02 INTEGER_2  Archive or Filtered flag.
                                       0: Archive
                                       1: filtered */
        MASK            = 0x37,   /* 0x06 STRING     Only in filtered streams. Layers and
                                       datatypes used for mask in a filtered stream
                                       file. A string giving ranges of layers and
                                       datatypes separated by a semicolon. There may
                                       be more than one mask in a stream file. */
        ENDMASKS        = 0x38,   /* 0x00 NO_DATA    The end of mask descriptions. */
        LIBDIRSIZE      = 0x39,   /* 0x02 INTEGER_2  Number of pages in library director, a GDSII
                                       thing, it seems to have only been used when
                                       Calma INFORM was creating a new library. */
        SRFNAME         = 0x3a,   /* 0x06 STRING     Sticks rule file name. */
        LIBSECUR        = 0x3b   /* 0x02 INTEGER_2  Access control list stuff for CalmaDOS,
                                       ancient. INFORM used this when creating a new
                                       library. Had 1 to 32 entries with group
                                       numbers, user numbers and access rights. */
    };
} // End namespace gdsfp

#endif // GDSCALMARECORDS_H_

