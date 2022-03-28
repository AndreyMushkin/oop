#include "translate_functions.h"

#include <iostream>
#include <algorithm>

constexpr auto EXIT_PHRASE = "...";
constexpr auto USER_INPUT_PREFIX = '>';

Operation GetOperationByUserInput(const std::string& userInput)
{
	if (userInput == EXIT_PHRASE)
	{
		//���������� Exit � ���� ���������
		return Operation::Exit;
	}

	return Operation::Translate;
}

bool PerformTranslation(Dictionary& dict, const std::string& word)
{
	std::optional<std::vector<std::string>> translations;
	std::string userTranslation;

	//�������� ������� � �������� �����
	translations = GetTranslations(word, dict);
	if (!translations.has_value())
	{
		std::cout << "����������� �����\"" << word << "\" ������� ������� ��� ������ ������ ��� ������." << std::endl;
		userTranslation = GetUserInput();
		if (!userTranslation.empty())
		{
			AddNewWord(dict, word, userTranslation);
			std::cout << "����� \"" << word << "\" ��������� � ������� ��� \"" << userTranslation << "\"." << std::endl;
			return true;
		}
		else
		{
			std::cout << "����� \"" << word << "\" ���������������." << std::endl;
		}
	}
	else
	{
		PrintTranslations(std::cout, translations.value());
	}

	return false;
}

bool AskForUpdatingDictionaryFile()
{
	std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������." << std::endl;
	char usrAnswer = std::cin.get();
	if (usrAnswer == 'Y' || usrAnswer == 'y')
	{
		return true;
	}

	return false;
}

std::optional<std::vector<std::string>> GetTranslations(const std::string& word, const Dictionary& dict)
{
	if (!dict.contains(word))
	{
		return std::nullopt;
	}

	return dict.at(word);
}

void AddNewWord(Dictionary& dict, const std::string& word, const std::string& translation)
{
	if (!dict.contains(word))
	{
		dict[word] = std::vector<std::string>{ translation };
	}
	else
	{
		dict[word].push_back(translation);
	}

	if (!dict.contains(translation))
	{
		dict[translation] = std::vector<std::string>{ word };
	}
	else
	{
		dict[translation].push_back(word);
	}
}

void PrintTranslations(std::ostream& out, const std::vector<std::string>& translations)
{
	bool first = true;
	for (std::string word : translations)
	{
		if (!first)
		{
			out << ", ";
		}
		else
		{
			first = false;
		}

		out << word;
	}

	out << std::endl;
}

std::string GetUserInput()
{
	std::string userInput;
	std::cout << USER_INPUT_PREFIX;
	std::getline(std::cin, userInput);

	return userInput;
}