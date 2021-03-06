//
#include "../std_lib_facilities.h"

const char number = '8'; // t.kind == number means that t is a number Token
const char quit = 'q';		// t.kind == quit means that t is a quit Token
const char print = ';';	// t.kind == print means that t is a print Token
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result
class Token {			// a very simple user-defined type
public:
  char kind;
  double value;
};

class Token_stream {
public:
  Token get();			// get a Token
  void putback(Token t);	// put a Token back
private:
  bool full {false};		// is there a Token in the buffer
  Token buffer;			// here is where we keep a Token put back using putback()
};

void Token_stream::putback(Token t)
{
  if (full) error("putback() into a full buffer");
  buffer = t;			// copy t to buffer
  full = true;			// buffer is now full
}

Token Token_stream::get()
{
  if (full) {			// do we already have a Token ready?
    full = false;		// remove Token from buffer
    return buffer;
  }
  char ch;
  cin >> ch;
  switch (ch) {
  case ';':			// for "print"
  case 'q':			// for "quit"
  case '(': case ')': case '+': case '-': case '*': case '/': case '%':
    return Token{ch};		// let each character represent it self
  case '.':
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
    {
      cin.putback(ch);		// put digit back into the input stream
      double val;
      cin >> val;		// read a floating-point number
      return Token{number, val};	// let '8' represent "a number"
    }
  default:
    error("Bad token");
  }
}

Token_stream ts;
double expression();

double primary()
{
  Token t = ts.get();
  switch (t.kind) {
  case '(':			// handle '(' expression ')'
    {
      double d = expression();
      t = ts.get();
      if (t.kind != ')') error("')' expected");
      return d;
    }
  case number:		       
    return t.value;		// return the number's value
  case '-':
    return -primary();
  case '+':
    return primary();
  default:
    error("primary expected");
  }
}

double term()
{
  double left = primary();
  Token t = ts.get();		// get the next Token from the Token stream
  while (true) {
    switch (t.kind) {
    case '*':
      left *= primary();
      t = ts.get();
      break;
    case '/':
      {
	double d = primary();
	if (d == 0) error("divide by zero");
	left /= d;
	t = ts.get();
	break;
      }
    case '%':
      {
	int i1 = narrow_cast<int>(left);
	int i2 = narrow_cast<int>(primary());
	if (i2 == 0) error("%: divide by zero");
	left = i1%i2;
	t = ts.get();
	break;
      }
    default:
      ts.putback(t);		// put t back into the Token stream
      return left;
    }
  }
}

double expression()
{
  double left = term();		// read and evaluate a Term
  Token t = ts.get();		// get the next token
  while (true) {
    switch (t.kind) {
    case '+':
      left += term();		// evaluate Term and add
      t = ts.get();
      break;
    case '-':
      left -= term();		// evaluate Term and subtract
      t = ts.get();
      break;
    default:
      ts.putback(t);	 // put t back into the token stream
      return left;		// finally: no more + or -; return the answer
    }
  }
}

int main()
  try {
    while (cin) {
      cout << prompt;
      Token t = ts.get();
      while (t.kind == print) t=ts.get(); // eat ';'
      if (t.kind == quit) {
	keep_window_open();
	return 0;
      }
      ts.putback(t);
      cout << result << expression() << '\n';
    }
  }
  catch (exception& e) {
    cerr << e.what() << '\n';
    keep_window_open("~~");
    return 1;
  }
  catch (...) {
    cerr << "exception \n";
    keep_window_open("~~");
    return 2;
  }

      
  
