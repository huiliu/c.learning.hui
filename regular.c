
#include "deelx.h"

int test_all_number( const char *string )
{
	//declare
	static CRegexpT <char> regexp("\\d+");
	
	//test
	MatchResult result = regexp.MatchExact( string );

	//matched or not 
	return result.IsMatched();
}

int main( int argc, char *argv[] )
{
	char *str1 = "12345";
	char *str2 = "12345 abcde";
	
	printf( "'%s' => %s\n'", str1, (test_all_number( str1 ) ? "yes":"no"));

	printf( "'%s' => %s\n'", str2, (test_all_number( str2 ) ? "yes":"no"));
}
