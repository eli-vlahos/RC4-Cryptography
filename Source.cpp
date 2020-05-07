#include <iostream>  
#include <cmath>
#include <cstdlib>

#ifndef MARMOSET_TESTING
int main();
#endif

char* encode(char* plaintext, unsigned long long key);
char* decode(char* ciphertext, unsigned long long key);
void keygenerator(unsigned char* plaintext, unsigned long long key, unsigned char* array, int counter);

#ifndef MARMOSET_TESTING
int main()
{
	char str0[]{ "A Elbereth Gilthoniel\nsilivren penna miriel\n"
"o menel aglar elenath!\nNa-chaered palan-diriel\n"
"o galadhremmin ennorath,\nFanuilos, le linnathon\n"
"nef aear, si nef aearon!" };

	char* ciphertext{ encode(str0, 51323) };
	char* plaintext{ decode(ciphertext, 51323) };
	std::cout << plaintext << std::endl;
	return 0;
}
#endif
char* encode(char* plaintext, unsigned long long key)
{
	int  counter = 0, realcounter = 0;

	while (plaintext[counter] != '\0')
	{
		plaintext[counter] = static_cast<unsigned char>(plaintext[counter]);
		counter++;
	}

	if (counter % 4 != 0)
	{
		realcounter = (counter + (4 - counter % 4));
	}
	else
		realcounter = counter;



	int counter4 = (realcounter / 4);
	unsigned char* newplaintext{ new unsigned char[realcounter + 1] {} };
	//have to use 

	for (int i = 0; i < realcounter + 1; i++)
	{
		if (i < counter)
			newplaintext[i] = plaintext[i];
		else
		{
			newplaintext[i] = '\0';

		}
	}


	char* final{ new char[(5 * (realcounter / 4)) + 1] { '\0' } };


	unsigned char* array{ new unsigned char[realcounter + 1] { } };

	keygenerator(newplaintext, key, array, realcounter);

	unsigned int sum1 = 0;
	for (int k = 0; k < counter4; k++)
	{
		sum1 = (array[4 * k] << 24) + (array[4 * k + 1] << 16) + (array[4 * k + 2] << 8) + array[4 * k + 3];


		for (int i = 4; i >= 0; i--)
		{
			final[k * 5 + i] = '!' + (sum1 % 85);
			sum1 /= 85;
		}
	}

	for (int i = 0; i < 205; i++)


		return final;
}
char* decode(char* ciphertext, unsigned long long key)
{


	int counter = 0;
	unsigned int sum = 0;

	while (ciphertext[counter] != '\0')
	{
		counter++;
	}

	unsigned	char* array{ new unsigned char[4 * (counter / 5) + 1]{'\0'} };
	unsigned char* decodetemp{ new unsigned char[4 * (counter / 5) + 1] { '\0' } };

	int counter5 = counter / 5;
	unsigned char thirty_zeros{ 0 };

	for (int k = 0; k < counter5; k++)
	{

		sum = 0;
		for (int i = 0; i < 5; i++)
		{
			sum = sum + (ciphertext[k * 5 + i] - '!') * static_cast<int>(pow(85, 4 - i));

		}
		std::cout << sum << std::endl;
		array[k * 4] = (sum >> 24) ^ thirty_zeros;


		array[k * 4 + 1] = (sum >> 16) ^ thirty_zeros;


		array[k * 4 + 2] = (sum >> 8) ^ thirty_zeros;


		array[k * 4 + 3] = sum ^ thirty_zeros;


	}


	keygenerator(array, key, decodetemp, 4 * (counter / 5));

	char* decode{ new char[4 * (counter / 5) + 1]{'\0'} };

	for (int i = 0; i < 4 * (counter / 5); i++)
	{
		decode[i] = decodetemp[i];

	}


	return decode;
}
void keygenerator(unsigned char* plaintext, unsigned long long key, unsigned char* array, int counter)
{
	unsigned long long i = 0, j = 0, k = 0;
	unsigned long long temp;


	unsigned long long sequence[256]{ 0 };

	for (int n = 0; n < 256; n++)
		sequence[n] = n;



	for (int m = 0; m < 256; m++)
	{
		k = i % 64;
		j += sequence[i] + ((key >> k) & 1UL);
		j %= 256;

		temp = sequence[i];
		sequence[i] = sequence[j];
		sequence[j] = temp;

		i = (i + 1) % 256;
	}


	int loop_i = 0;
	while (loop_i <= counter)
	{

		i = (i + 1) % 256;
		j = (j + sequence[i]) % 256;

		temp = sequence[i];
		sequence[i] = sequence[j];
		sequence[j] = temp;


		unsigned char r = (sequence[j] + sequence[i]) % 256;
		unsigned char R = sequence[r];


		array[loop_i] = R ^ static_cast<unsigned char>(plaintext[loop_i]);

		loop_i++;

	}
	std::cout << std::endl;

}

