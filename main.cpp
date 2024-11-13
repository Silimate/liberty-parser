#include <iostream>
#include <string>
#include "include/si2dr_liberty.h"

// Logger (info)
void log(std::string msg) {
  std::cout << msg;
}

// Logger (error)
void log_error(std::string msg) {
  std::cerr << msg;
}

// C++ wrapper for Synopsys Liberty parser
class LibertyParser {
  public:
    // Constructor
    LibertyParser(std::string filename) {
      si2drPIInit(&err); 
	    si2drReadLibertyFile(strdup(filename.c_str()), &err);
      groups = si2drPIGetGroups(&err);
    }
    // Destructor
    ~LibertyParser() {
      si2drPIQuit(&err);
    }
    // Check the Liberty database
    void check() {
	    si2drGroupIdT group;
      while (!si2drObjectIsNull((group=si2drIterNextGroup(groups, &err)), &err)) {
        log("Checking the Liberty database...\n");
		    si2drCheckLibertyLibrary(group, &err);
        if (err == SI2DR_NO_ERROR) log("  Passed!\n");
		    else log_error("  Errors detected!\n");
	    }
	    si2drIterQuit(groups, &err);
    }
    // Get the error text
    std::string get_error_text() {
      return si2drPIGetErrorText(err, &err);
    }
  private:
    si2drErrorT err; // error
    si2drGroupsIdT groups; // groups in the Liberty database
};

// Main method
int main(int argc, char *argv[]) {
  LibertyParser parser(argv[1]);
  parser.check();
  return 0;
}
