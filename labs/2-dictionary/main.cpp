#include <iostream>

#include "lib/translate_functions.h"
#include "lib/file_stream_utils.h"

constexpr auto ARGS_COUNT = 2;
constexpr auto USER_INPUT_PREFIX = '>';

std::optional<std::string> ParseDictFileNameArg(int argc, char* argv[]);
std::string GetUserInput();

int main(int argc, char* argv[])
{
	auto arg = ParseDictFileNameArg(argc, argv);
	if (!arg.has_value())
	{
		std::cout << "������ ��㬥��� ��������� ��ப�. �ਬ��: 2-dictionary.exe <���� �� 䠩�� ᫮����>" << std::endl;
		return 1;
	}

	std::string dictFileName = arg.value();
	std::fstream dictFile;
	if (!OpenFileStream(dictFile, dictFileName, std::ios::in))
	{
		std::cout << "�� 㤠���� ������ 䠩� ᫮����. ��������, �� 䠩� ������� � ����㯥� ��� �⥭��." << std::endl;
		return 1;
	}

	Dictionary dictionary = ReadDictionary(dictFile);
	bool dictWasModified = false;
	Operation operation;
	std::string userInput, userTranslation;
	std::optional<std::vector<std::string>> translations;

	do
	{
		userInput = GetUserInput();
		operation = PerformOperationByUserInput(userInput, dictWasModified);

		switch (operation)
		{
		case Operation::TranslateFromEn:
		case Operation::TranslateFromRu:
			(operation == Operation::TranslateFromRu) ? 
				translations = GetRuWordTranslations(userInput, dictionary) : 
				translations = GetEnWordTranslations(userInput, dictionary);
			if (!translations.has_value())
			{
				std::cout << "�� ������ ��ॢ�� ��� ᫮�� \"" << userInput << "\" ������ ��ॢ�� ��� ������ ��ப� ��� �⪠��." << std::endl;
				userTranslation = GetUserInput();
				if (!userTranslation.empty())
				{
					(operation == Operation::TranslateFromRu) ? 
						AddNewRuWord(dictionary, userInput, userTranslation) : 
						AddNewEnWord(dictionary, userInput, userTranslation);
					std::cout << "����� \"" << userInput << "\" ��࠭��� � ᫮��� ��� \"" << userTranslation << "\"." << std::endl;
					dictWasModified = true;
				}
				else
				{
					std::cout << "����� \"" << userInput << "\" �ந����஢���." << std::endl;
				}
			}
			else
			{
				PrintTranslations(std::cout, translations.value());
			}
			break;
		case Operation::ExitAndSaveChanges:
			if (!OpenFileStream(dictFile, dictFileName, std::ios::out) || !RewriteDictionary(dictFile, dictionary))
			{
				std::cout << "�� 㤠���� ��࠭��� ��������� � 䠩� ᫮����." << std::endl;
			}
			else
			{
				std::cout << "��������� ��࠭���. ";
			}
			break;
		case Operation::ExitAndDiscardChanges:
			std::cout << "��������� �� �뫨 ���ᥭ� � ᫮����. ";
			break;
		case Operation::BadInput:
			std::cout << "������� �����४⭮� ᫮��. ���஡�� ᭮��..." << std::endl;
			break;
		default:
			break;
		}

	} while (operation != Operation::ExitAndSaveChanges && operation != Operation::ExitAndDiscardChanges);

	std::cout << "�� ᢨ�����." << std::endl;

	return 0;
}

std::optional<std::string> ParseDictFileNameArg(int argc, char* argv[])
{
	if (argc != ARGS_COUNT)
	{
		return std::nullopt;
	}

	return std::string(argv[1]);
}

std::string GetUserInput()
{
	std::string userInput;
	std::cout << USER_INPUT_PREFIX;
	std::getline(std::cin, userInput);

	return userInput;
}
