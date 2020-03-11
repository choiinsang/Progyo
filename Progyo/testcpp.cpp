#include <iostream>
#include <string.h>

using namespace std;
#define STRLEN_CodeResult 50

const char gStrCodeRes_temporary_user[][STRLEN_CodeResult] = {
	"suspended user",
	"over quota",
	"greenlist.html",
	"out of memory",
	"mailbox full",
	"insufficient",
	"inactive",
	"many",
	"exceed",
	"temporarily disabled"
};

int main(int argc, char *argv[]){
  cout <<  "=> "  << sizeof(gStrCodeRes_temporary_user) / STRLEN_CodeResult << endl;
  return 0;
}
