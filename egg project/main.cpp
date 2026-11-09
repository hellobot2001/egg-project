#include <iostream>
#include <vector>

using namespace std;

class egg {
protected:
	int size;
	string flavor;
public:
	egg(int s, string f)
	{
		size = s;
		flavor = f;
	}

	virtual void eat_egg() = 0;
};

class bad_egg : public exception {
public:

	const char* what() const {
		return "this egg is bad!";
	}
};

class rotten_egg : public egg {
public:
	rotten_egg(int s) : egg(s, "BAD!!!!!") {}
	void eat_egg() { throw bad_egg(); }
};

class double_egg : public egg {
public:
	double_egg(int s) : egg(s + 2, "like it has 2 yolks!") {}
	void eat_egg() { cout << "this size " << size << " egg tastes " << flavor << endl; }
};

class int_egg : public egg {
public:
	int_egg(int s) : egg(s + 1, "like it is a bad joke based on the fact that the 2 yolk egg has a class name with 'double' in it!") {}
	void eat_egg() { cout << "this size " << size << " egg tastes " << flavor << endl; }
};

class normal_egg : public egg {
public:
	normal_egg(int s) : egg(s, "like an egg") {}
	void eat_egg() { cout << "this size " << size << " egg tastes " << flavor << endl; }
};

class carton {
private:
	int count = 12;
	vector<egg*> e;
public:
	carton()
	{
		int t = time(0); srand(t);
		for (int i = 0; i < 12; i++)
		{
			if (rand() % 64 > 23)
			{
				normal_egg* n = new normal_egg((rand() % 5) + 1);
				e.push_back(n);
			}
			else if (rand() % 16 < 12)
			{
				rotten_egg* n = new rotten_egg((rand() % 5) + 1);
				e.push_back(n);
			}
			else if (rand() % 16 < 8)
			{
				double_egg* n = new double_egg((rand() % 5) + 1);
				e.push_back(n);
			}
			else
			{
				int_egg* n = new int_egg((rand() % 5) + 1);
				e.push_back(n);
			}
		}
	}

	void take_egg()
	{
		try
		{
			egg* f = e[count - 1];
			e.pop_back();
			count--;
			f->eat_egg();
		}
		catch (bad_egg b)
		{
			cout << b.what() << endl;
		}
	}
};

int main()
{
	carton c;
	for (int i = 0; i < 12; i++)
	{
		c.take_egg();
	}
}