/*
  ==============================================================================

   This file is part of the eJUCE library
   which is based on Raw Material Software ltd. JUCE

   eJUCE can be redistributed and/or modified under the terms of the
   GNU General Public License, as published by the Free Software Foundation;
   either version 2 of the License, or (at your option) any later version.

   eJUCE is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with eJUCE; if not, visit www.gnu.org/licenses or write to the
   Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
   Boston, MA 02111-1307 USA

   @author	Asnaghi Lucio

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#pragma warning(push)
#pragma warning(disable:4244)
#include "pcre/pcre.h"
#pragma warning(pop)
#include "ejuce_RegularExpression.h"



//==============================================================================
RegularExpression::RegularExpression() :
	numSubStrings (0),
	pattern (String::empty),
	subject (String::empty)
{
}

RegularExpression::RegularExpression( const String& pattern_ ) :
	pattern(pattern_),
	subject(String::empty),
	numSubStrings(0)
{
}

RegularExpression::~RegularExpression()
{
}

String RegularExpression::operator[] (const int index)
{
    if (isPositiveAndBelow (index, numSubStrings))
    {
		int start, end;
        return getStringOffsetSize(index, start, end);
    }

    return String::empty;
}

int RegularExpression::match( const String& pattern_, const String& subject_ )
{
	pattern = pattern_;
	return match(subject_);
}

int RegularExpression::match( const String& subject_ )
{
	subject = subject_;

	pcre* re;
	const char *error;
	int erroffset;
	int ovector[OVECOUNT];
	memset(ovector,0,OVECOUNT*sizeof(int));

	index.clear();

	// try to compile
	re = pcre_compile(
			pattern.toRawUTF8(),	// the pattern
			0,						// default options
			&error,					// for error message
			&erroffset,				// for error offset
			0);						// use default character tables

	// compilation failed
	if (re == 0)
	{
		return compileFailed;
	}

	// execute
	numSubStrings = pcre_exec(
			re,						// the compiled pattern
			0,						// no extra data - we didn't study the pattern
			subject.toRawUTF8(),	// the subject string
			subject.length(),		// the length of the subject
			0,						// start at offset 0 in the subject
			0,						// default options
			ovector,				// output vector for substring information
			OVECOUNT);				// number of elements in the output vector

	// matching error checking
	if (numSubStrings < 0)
	{
		switch(numSubStrings)
		{
			case PCRE_ERROR_NOMATCH:
				free(re);
				return matchNotFound;
			default:
				free(re);
				return matchFindError;
		}
	}

	// The match succeeded, but the output vector wasn't big enough.
	if (numSubStrings == 0)
	{
		return bufferSizeError;
	}

	// else add stuff
    for (int i = 0; i < numSubStrings; i++)
	{
		index.add(new ExpressionIndex(ovector[2*i],ovector[2*i+1]));
	}

	for (;;)
	{
		int options = 0;
		int start_offset = ovector[1];

		if (ovector[0] == ovector[1])
		{
			if (ovector[0] == subject.length())
				break;
			options = PCRE_NOTEMPTY | PCRE_ANCHORED;
		}

		int thisSubStrings = pcre_exec(
			re,						// pattern
			0,						// no extra
			subject.toRawUTF8(),	// the subject string
			subject.length(),		// the length of the subject
			start_offset,			// starting offset in the subject
			options,				// options
			ovector,				// output vector for substring information
			OVECOUNT);			// number of elements in the output vector

		if (thisSubStrings == PCRE_ERROR_NOMATCH)
		{
			if (options == 0) break;
			ovector[1] = start_offset + 1;
			continue;    // Go round the loop again
		}

		// Other matching errors are not recoverable.
		if (thisSubStrings < 0)
		{
			free(re);
			return matchFindError;
		}

		// The match succeeded, but the output vector wasn't big enough.
		if (thisSubStrings == 0)
		{
			continue;
		}

	    for (int i = 0; i < thisSubStrings; i++)
		{
			index.add(new ExpressionIndex(ovector[2*i],ovector[2*i+1]));
		}

		numSubStrings += thisSubStrings;

	}

	free(re);

	return (numSubStrings);
}

String RegularExpression::getStringOffsetSize( int num, int& start, int& end )
{
	jassert( num < numSubStrings );

	start = index[num]->start;
	end = index[num]->end;

	return subject.substring(start,end);
}

