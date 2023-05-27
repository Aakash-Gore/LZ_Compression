#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

void encode(string s)
{

	const int w = 50;
	string lookup_window[w];
	for (int i = 0; i < w; i++)
	{
		if (i < 26)
			lookup_window[i] = char(i + 97);
		else
			lookup_window[i] = "";
         
	}
	int match;
	string str = "";
	string lookup = "";
	bool found = false;
	int a = 26;
	for (auto& i : s)
	{
		string temp;
		temp = i;

		if (str == "")
		{
			str = i;
			match = int(i) - 97;
			continue;
		}
		lookup = str;
		lookup.append(temp);
		for (int j = 0; j < w; j++)
		{
			if (lookup == lookup_window[j])
			{
				found = true;
				match = j;
				//break;
			}
		}

		if (found == false)
		{
			lookup_window[a] = lookup;

			for (int j = 0; j < w; j++)
			{
				if (str == lookup_window[j])
				{
					match = j;
					
				}
			}

			str = i;
			cout << match << endl;
			a++;
		}
		else
		{
			str.append(temp);
			found = false;
		}
	}
}
		 

int main()
{
	string s = "abcabcabcabcabc";
	encode(s);
}