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

#ifndef __EJUCE_REGULAREXPRESSION__
#define __EJUCE_REGULAREXPRESSION__


//==============================================================================
/**
    This class is designed around PCRE library for regular expression
	parsing and evaluating

    e.g. @code
    RegularExpression re("\\d{3}");
    int found = re.match("123.345");

    if ( found >= 0 )
    {
        int o, e;
        for( int i=0; i<found; i++ )
        {
            String s = "";
            String result = re.getStringOffsetSize(i,o,e);

            s << "'" << result << "' - (" << o << "," << e << ")" ;
            AlertWindow::showMessageBox(AlertWindow::WarningIcon,T(""),s);
        }
    }
    else
        AlertWindow::showMessageBox(AlertWindow::WarningIcon,T(""),T("not found anything"));

    @endcode

*/
//class String;

class RegularExpression
{
public:

	enum {
		OVECOUNT = 30,
		compileFailed = -100,
		bufferSizeError = -101,		
		matchNotFound = -102,
		matchFindError = -103
	};

	RegularExpression();
	RegularExpression( const String& pattern );
	~RegularExpression();

	String operator[] (const int index);

	int match( const String& subject );
	int match( const String& pattern, const String& subject );
    String getStringOffsetSize( int num, int& start, int& end );
   
private:

	class ExpressionIndex
	{
	public:
		ExpressionIndex(int s, int e)
			: start(s), end(e) { }
		int start;
		int end;
	};

	int numSubStrings;

	OwnedArray<ExpressionIndex> index;

	String pattern;
	String subject;

	RegularExpression(const RegularExpression& other);
};

#endif // __EJUCE_REGULAREXPRESSION__
