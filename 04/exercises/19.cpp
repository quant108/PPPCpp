// names and scores
#include "../../std_lib_facilities.h"
int main()
{
  vector<string> names;
  string name;
  vector<double> scores;
  double score;

  int quit = 0;			// do not quit
  for(; quit == 0;) {
    if (cin >> name >> score)
      ;
    else
      quit = 1;

    if ((name == "NoName") && (score == 0))
      quit = 1;

    if (quit == 0) {
      for (int i = 0; i < scores.size(); ++i)
	if (name == names[i]) {
	  quit = 1;
	  cout << "There is a name exist: " << name << '\n';
	}
    }
    
    if (quit == 0) {
      names.push_back(name);
      scores.push_back(score);
    }
  }

  cout << "\n\n" << "Name" << '\t' << "Score" << '\n';
  
  for (int i = 0; i < names.size(); ++i) 
    cout << names[i] << '\t' << scores[i] << '\n';

  return 0;
}
