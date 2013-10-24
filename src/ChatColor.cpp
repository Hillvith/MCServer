
#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

#include "ChatColor.h"

const std::string cChatColor::Color     = "\xc2\xa7";  // or in other words: "§" in UTF-8
const std::string cChatColor::Delimiter = "\xc2\xa7";  // or in other words: "§" in UTF-8
const std::string cChatColor::Black       = cChatColor::Color + "0";
const std::string cChatColor::Navy        = cChatColor::Color + "1";
const std::string cChatColor::Green       = cChatColor::Color + "2";
const std::string cChatColor::Blue        = cChatColor::Color + "3";
const std::string cChatColor::Red         = cChatColor::Color + "4";
const std::string cChatColor::Purple      = cChatColor::Color + "5";
const std::string cChatColor::Gold        = cChatColor::Color + "6";
const std::string cChatColor::LightGray   = cChatColor::Color + "7";
const std::string cChatColor::Gray        = cChatColor::Color + "8";
const std::string cChatColor::DarkPurple  = cChatColor::Color + "9";
const std::string cChatColor::LightGreen  = cChatColor::Color + "a";
const std::string cChatColor::LightBlue   = cChatColor::Color + "b";
const std::string cChatColor::Rose        = cChatColor::Color + "c";
const std::string cChatColor::LightPurple = cChatColor::Color + "d";
const std::string cChatColor::Yellow      = cChatColor::Color + "e";
const std::string cChatColor::White       = cChatColor::Color + "f";

const std::string cChatColor::Random      = cChatColor::Color + "k";
const std::string cChatColor::Bold        = cChatColor::Color + "l";
const std::string cChatColor::Strikethrough = cChatColor::Color + "m";
const std::string cChatColor::Underlined  = cChatColor::Color + "n";
const std::string cChatColor::Italic      = cChatColor::Color + "o";
const std::string cChatColor::Plain       = cChatColor::Color + "r";

const std::string cChatColor::MakeColor( char a_Color )
{
	return cChatColor::Color + a_Color;
}




