/***************************************************************************
    copyright           : (C) 2010 by Lukas Lalinsky
    email               : lukas@oxygene.sk
 ***************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License version   *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA         *
 *   02110-1301  USA                                                       *
 *                                                                         *
 *   Alternatively, this file is available under the Mozilla Public        *
 *   License Version 1.1.  You may obtain a copy of the License at         *
 *   http://www.mozilla.org/MPL/                                           *
 ***************************************************************************/

#include <string>
#include <cstdio>
#include "apetag.h"
#include "id3v1tag.h"
#include "tstringlist.h"
#include "tbytevectorlist.h"
#include "tpropertymap.h"
#include "apefile.h"
#include <cppunit/extensions/HelperMacros.h>
#include "utils.h"

using namespace std;
using namespace TagLib;

class TestAPE : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(TestAPE);
  CPPUNIT_TEST(testProperties399);
  CPPUNIT_TEST(testProperties399Tagged);
  CPPUNIT_TEST(testProperties399Id3v2);
  CPPUNIT_TEST(testProperties396);
  CPPUNIT_TEST(testProperties390);
  CPPUNIT_TEST(testFuzzedFile1);
  CPPUNIT_TEST(testFuzzedFile2);
  CPPUNIT_TEST(testStripAndProperties);
  CPPUNIT_TEST(testRepeatedSave);
  CPPUNIT_TEST_SUITE_END();

public:

  void testProperties399()
  {
    APE::File f(TEST_FILE_PATH_C("mac-399.ape"));
    CPPUNIT_ASSERT(f.audioProperties());
    CPPUNIT_ASSERT_EQUAL(3, f.audioProperties()->lengthInSeconds());
    CPPUNIT_ASSERT_EQUAL(3550, f.audioProperties()->lengthInMilliseconds());
    CPPUNIT_ASSERT_EQUAL(192, f.audioProperties()->bitrate());
    CPPUNIT_ASSERT_EQUAL(2, f.audioProperties()->channels());
    CPPUNIT_ASSERT_EQUAL(44100, f.audioProperties()->sampleRate());
    CPPUNIT_ASSERT_EQUAL(16, f.audioProperties()->bitsPerSample());
    CPPUNIT_ASSERT_EQUAL(156556U, f.audioProperties()->sampleFrames());
    CPPUNIT_ASSERT_EQUAL(3990, f.audioProperties()->version());
  }

  void testProperties399Tagged()
  {
    APE::File f(TEST_FILE_PATH_C("mac-399-tagged.ape"));
    CPPUNIT_ASSERT(f.audioProperties());
    CPPUNIT_ASSERT_EQUAL(3, f.audioProperties()->lengthInSeconds());
    CPPUNIT_ASSERT_EQUAL(3550, f.audioProperties()->lengthInMilliseconds());
    CPPUNIT_ASSERT_EQUAL(192, f.audioProperties()->bitrate());
    CPPUNIT_ASSERT_EQUAL(2, f.audioProperties()->channels());
    CPPUNIT_ASSERT_EQUAL(44100, f.audioProperties()->sampleRate());
    CPPUNIT_ASSERT_EQUAL(16, f.audioProperties()->bitsPerSample());
    CPPUNIT_ASSERT_EQUAL(156556U, f.audioProperties()->sampleFrames());
    CPPUNIT_ASSERT_EQUAL(3990, f.audioProperties()->version());
  }

  void testProperties399Id3v2()
  {
    APE::File f(TEST_FILE_PATH_C("mac-399-id3v2.ape"));
    CPPUNIT_ASSERT(f.audioProperties());
    CPPUNIT_ASSERT_EQUAL(3, f.audioProperties()->lengthInSeconds());
    CPPUNIT_ASSERT_EQUAL(3550, f.audioProperties()->lengthInMilliseconds());
    CPPUNIT_ASSERT_EQUAL(192, f.audioProperties()->bitrate());
    CPPUNIT_ASSERT_EQUAL(2, f.audioProperties()->channels());
    CPPUNIT_ASSERT_EQUAL(44100, f.audioProperties()->sampleRate());
    CPPUNIT_ASSERT_EQUAL(16, f.audioProperties()->bitsPerSample());
    CPPUNIT_ASSERT_EQUAL(156556U, f.audioProperties()->sampleFrames());
    CPPUNIT_ASSERT_EQUAL(3990, f.audioProperties()->version());
  }

  void testProperties396()
  {
    APE::File f(TEST_FILE_PATH_C("mac-396.ape"));
    CPPUNIT_ASSERT(f.audioProperties());
    CPPUNIT_ASSERT_EQUAL(3, f.audioProperties()->lengthInSeconds());
    CPPUNIT_ASSERT_EQUAL(3685, f.audioProperties()->lengthInMilliseconds());
    CPPUNIT_ASSERT_EQUAL(0, f.audioProperties()->bitrate());
    CPPUNIT_ASSERT_EQUAL(2, f.audioProperties()->channels());
    CPPUNIT_ASSERT_EQUAL(44100, f.audioProperties()->sampleRate());
    CPPUNIT_ASSERT_EQUAL(16, f.audioProperties()->bitsPerSample());
    CPPUNIT_ASSERT_EQUAL(162496U, f.audioProperties()->sampleFrames());
    CPPUNIT_ASSERT_EQUAL(3960, f.audioProperties()->version());
  }

  void testProperties390()
  {
    APE::File f(TEST_FILE_PATH_C("mac-390-hdr.ape"));
    CPPUNIT_ASSERT(f.audioProperties());
    CPPUNIT_ASSERT_EQUAL(15, f.audioProperties()->lengthInSeconds());
    CPPUNIT_ASSERT_EQUAL(15630, f.audioProperties()->lengthInMilliseconds());
    CPPUNIT_ASSERT_EQUAL(0, f.audioProperties()->bitrate());
    CPPUNIT_ASSERT_EQUAL(2, f.audioProperties()->channels());
    CPPUNIT_ASSERT_EQUAL(44100, f.audioProperties()->sampleRate());
    CPPUNIT_ASSERT_EQUAL(16, f.audioProperties()->bitsPerSample());
    CPPUNIT_ASSERT_EQUAL(689262U, f.audioProperties()->sampleFrames());
    CPPUNIT_ASSERT_EQUAL(3900, f.audioProperties()->version());
  }

  void testFuzzedFile1()
  {
    APE::File f(TEST_FILE_PATH_C("longloop.ape"));
    CPPUNIT_ASSERT(f.isValid());
  }

  void testFuzzedFile2()
  {
    APE::File f(TEST_FILE_PATH_C("zerodiv.ape"));
    CPPUNIT_ASSERT(f.isValid());
  }

  void testStripAndProperties()
  {
    ScopedFileCopy copy("mac-399", ".ape");

    {
      APE::File f(copy.fileName().c_str());
      f.APETag(true)->setTitle("APE");
      f.ID3v1Tag(true)->setTitle("ID3v1");
      f.save();
    }
    {
      APE::File f(copy.fileName().c_str());
      CPPUNIT_ASSERT_EQUAL(String("APE"), f.properties()["TITLE"].front());
      f.strip(APE::File::APE);
      CPPUNIT_ASSERT_EQUAL(String("ID3v1"), f.properties()["TITLE"].front());
      f.strip(APE::File::ID3v1);
      CPPUNIT_ASSERT(f.properties().isEmpty());
    }
  }

  void testProperties()
  {
    PropertyMap tags;
    tags["ALBUM"] = StringList("Album");
    tags["ALBUMARTIST"] = StringList("Album Artist");
    tags["ALBUMARTISTSORT"] = StringList("Album Artist Sort");
    tags["ALBUMSORT"] = StringList("Album Sort");
    tags["ARTIST"] = StringList("Artist");
    tags["ARTISTS"] = StringList("Artists");
    tags["ARTISTSORT"] = StringList("Artist Sort");
    tags["ASIN"] = StringList("ASIN");
    tags["BARCODE"] = StringList("Barcode");
    tags["CATALOGNUMBER"] = StringList("Catalog Number 1").append("Catalog Number 2");
    tags["COMMENT"] = StringList("Comment");
    tags["DATE"] = StringList("2021-01-10");
    tags["DISCNUMBER"] = StringList("3/5");
    tags["GENRE"] = StringList("Genre");
    tags["ISRC"] = StringList("UKAAA0500001");
    tags["LABEL"] = StringList("Label 1").append("Label 2");
    tags["MEDIA"] = StringList("Media");
    tags["MUSICBRAINZ_ALBUMARTISTID"] = StringList("MusicBrainz_AlbumartistID");
    tags["MUSICBRAINZ_ALBUMID"] = StringList("MusicBrainz_AlbumID");
    tags["MUSICBRAINZ_ARTISTID"] = StringList("MusicBrainz_ArtistID");
    tags["MUSICBRAINZ_RELEASEGROUPID"] = StringList("MusicBrainz_ReleasegroupID");
    tags["MUSICBRAINZ_RELEASETRACKID"] = StringList("MusicBrainz_ReleasetrackID");
    tags["MUSICBRAINZ_TRACKID"] = StringList("MusicBrainz_TrackID");
    tags["ORIGINALDATE"] = StringList("2021-01-09");
    tags["RELEASECOUNTRY"] = StringList("Release Country");
    tags["RELEASESTATUS"] = StringList("Release Status");
    tags["RELEASETYPE"] = StringList("Release Type");
    tags["SCRIPT"] = StringList("Script");
    tags["TITLE"] = StringList("Title");
    tags["TRACKNUMBER"] = StringList("2/3");

    ScopedFileCopy copy("mac-399", ".ape");
    {
      APE::File f(copy.fileName().c_str());
      PropertyMap properties = f.properties();
      CPPUNIT_ASSERT(properties.isEmpty());
      f.setProperties(tags);
      f.save();
    }
    {
      const APE::File f(copy.fileName().c_str());
      PropertyMap properties = f.properties();
      if (tags != properties) {
        CPPUNIT_ASSERT_EQUAL(tags.toString(), properties.toString());
      }
      CPPUNIT_ASSERT(tags == properties);
    }
  }

  void testRepeatedSave()
  {
    ScopedFileCopy copy("mac-399", ".ape");

    {
      APE::File f(copy.fileName().c_str());
      CPPUNIT_ASSERT(!f.hasAPETag());
      CPPUNIT_ASSERT(!f.hasID3v1Tag());

      f.APETag(true)->setTitle("01234 56789 ABCDE FGHIJ");
      f.save();

      f.APETag()->setTitle("0");
      f.save();

      f.ID3v1Tag(true)->setTitle("01234 56789 ABCDE FGHIJ");
      f.APETag()->setTitle("01234 56789 ABCDE FGHIJ 01234 56789 ABCDE FGHIJ 01234 56789");
      f.save();
    }
    {
      APE::File f(copy.fileName().c_str());
      CPPUNIT_ASSERT(f.hasAPETag());
      CPPUNIT_ASSERT(f.hasID3v1Tag());
    }
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(TestAPE);
