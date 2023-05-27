#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<fstream>
#include <sstream>

using namespace std;
ofstream op1("compressed.txt");
string encode(string s)
{
	string st;
	st.append(" ");
	op1 << ' ';
	const int w = 20;
	int part = 12;
	char sliding_window[w];

	
    
	int o;
	int l;
	char code = s[0];
	bool match = false;
	int c = 0;


	for (int i = 0; i < w - part; i++)
	{
		s.append(" ");
	}

	for (int i = 0; i < w; i++)
	{
		if (i < part)
		{
			sliding_window[i] = ' ';
		}
		else
			sliding_window[i] = s[i - part];
	}

	int max1 = 0;
	int omax = 0;

	for (int i = w-part; i < s.size(); i++)
	{
		for (int j = part -1; j > 0; j--)
		{
			if (sliding_window[part] == sliding_window[j])
			{
				match = true;
				//omax = j;
				int c = 0;
				int k = 0;
				
				while (k < w-part)
				{
					k++;
					if (sliding_window[j+c] == sliding_window[part + c])
					{
						c++;

					}
					else
					{
						if(max1<c)
						{
							max1 = c;
							omax = j;
						}
						
					}
					

				}


				
			
			}
        
		}
		if (match == false)
		{
			code = sliding_window[part];
			o = 0;
			l = 1;
			op1 << o << code << l << " ";
			st.append(to_string(o));
			st.append(1, code);
			st.append(to_string(l));
			st.append(" ");
			for (int a = 0; a < w - 1; a++)
			{
				sliding_window[a] = sliding_window[a + 1];
			}
			sliding_window[w - 1] = s[i];
		}
		if(match == true)
		{
			o = part - omax;
			l = max1;
			max1 = 0;
			code = s[i - w + part + l];
			

			for (int a = 0; a < w ; a++)
			{
				if(a<w-l-1)
					sliding_window[a] = sliding_window[a + l+1];
				else
					sliding_window[a] = s[i+a-w+l+1];
				
			}
			i += l;
			op1 << o << code<< l << " ";
			st.append(to_string(o));
			st.append(1, code);
			st.append(to_string(l));
			st.append(" ");
			match = false;
			
			
		}

		
	}
	
	
	return st;

}


void decode(string s)
{
	ofstream op2("decompressed.txt");
	string st;
	int b = 0;
	for (int i = 0; i < s.size()-1; i++)
	{
		if (s[i] == ' ')
		{
			b = i;

		}
		
	}

	for (int i = 0; i < s.size(); i++)
	{
		string temp;
		
		int a = 1;
		int o = 0;
		double l = 0;
		if ((s[i] > 96 && s[i] < 123) || b == i)
		{

			while (s[i - a] != ' ')
			{
				o = 10 * o + (int(s[i - a]) - 48);
				a++;
			}
			a = 1;
			while (s[i + a] != ' ')
			{
				l = l + (int(s[i + a]) - 48) / (pow(10, a));
				a++;
			}
			l = pow(10, a-1) * l;

			if (o == 0)
			{

				temp = s[i];
				st.append(temp);
			}
			else
			{
				int k = st.size();
				for (int x = 0; x < l; x++)
				{

					temp = st[ k- o + x];
					st.append(temp);
				}
				temp = s[i];
				st.append(temp);

			}
		}

	}
	op2 << st;
}


int main()

{
	
	ifstream myfile;
	myfile.open("text.txt");

	stringstream buffer;
	buffer << myfile.rdbuf();

	string s = buffer.str();
	myfile.close();

	

	
	


	
	decode(encode(s));
}