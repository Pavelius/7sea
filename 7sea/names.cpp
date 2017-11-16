#include "main.h"

static struct name_t
{
    nation_s			nation;
    gender_s			gender;
    const char*			name[2];
} name_data[] =
{
    {Avalon, Male, {"", "Эйден"}},
    {Avalon, Male, {"", "Алан"}},
    {Avalon, Male, {"", "Бран"}},
    {Avalon, Male, {"", "Дуайер"}},
    {Avalon, Male, {"", "Эдуард"}},
    {Avalon, Male, {"", "Финн"}},
    {Avalon, Male, {"", "Гарольд"}},
    {Avalon, Male, {"", "Джером"}},
    {Avalon, Male, {"", "Кейт"}},
    {Avalon, Male, {"", "Лиам"}},
    {Avalon, Male, {"", "Люк"}},
    {Avalon, Male, {"", "Малькольм"}},
    {Avalon, Male, {"", "Майкл"}},
    {Avalon, Male, {"", "Морган"}},
    {Avalon, Male, {"", "Оссиан"}},
    {Avalon, Male, {"", "Квинн"}},
    {Avalon, Male, {"", "Ричард"}},
    {Avalon, Male, {"", "Шоун"}},
    {Avalon, Male, {"", "Томас"}},
    {Avalon, Male, {"", "Уолтер"}},
    {Avalon, Female, {"", "Эйлин"}},
    {Avalon, Female, {"", "Элисон"}},
    {Avalon, Female, {"", "Бриджит"}},
    {Avalon, Female, {"", "Кэролайн"}},
    {Avalon, Female, {"", "Дениз"}},
    {Avalon, Female, {"", "Элейн"}},
    {Avalon, Female, {"", "Грейс"}},
    {Avalon, Female, {"", "Хелен"}},
    {Avalon, Female, {"", "Джейн"}},
    {Avalon, Female, {"", "Карен"}},
    {Avalon, Female, {"", "Лейла"}},
    {Avalon, Female, {"", "Мэв"}},
    {Avalon, Female, {"", "Мэри"}},
    {Avalon, Female, {"", "Памелла"}},
    {Avalon, Female, {"", "Саббина"}},
    {Avalon, Female, {"", "Сибил"}},
    {Avalon, Female, {"", "Тереза"}},
    {Avalon, Female, {"", "Вероника"}},
    {Avalon, Female, {"", "Джейн"}},
    {Avalon, Female, {"", "Элизабет"}},
    {Castille, Male, {"", "Алонсо"}},
    {Castille, Male, {"", "Андрес"}},
    {Castille, Male, {"", "Балтазар"}},
    {Castille, Male, {"", "Бенито"}},
    {Castille, Male, {"Carlos", "Карлос"}},
    {Castille, Male, {"Diego", "Диего"}},
    {Castille, Male, {"Domingo", "Доминго"}},
    {Castille, Male, {"Esteban", "Эстебан"}},
    {Castille, Male, {"", "Фелипе"}},
    {Castille, Male, {"", "Гаспар"}},
    {Castille, Male, {"", "Гектор"}},
    {Castille, Male, {"", "Джейм"}},
    {Castille, Male, {"", "Хуан"}},
    {Castille, Male, {"", "Лукас"}},
    {Castille, Male, {"Migel", "Мигель"}},
    {Castille, Male, {"Rodrigo", "Родриго"}},
    {Castille, Male, {"Sancho", "Санчо"}},
    {Castille, Male, {"", "Себастьян"}},
    {Castille, Male, {"", "Томас"}},
    {Castille, Female, {"", "Андреа"}},
    {Castille, Female, {"", "Анжела"}},
    {Castille, Female, {"", "Беатрис"}},
    {Castille, Female, {"", "Каталина"}},
    {Castille, Female, {"", "Клара"}},
    {Castille, Female, {"", "Констанца"}},
    {Castille, Female, {"", "Кристина"}},
    {Castille, Female, {"", "Флориана"}},
    {Castille, Female, {"", "Франциска"}},
    {Castille, Female, {"", "Инесса"}},
    {Castille, Female, {"", "Изабелла"}},
    {Castille, Female, {"", "Джулиана"}},
    {Castille, Female, {"", "Люсия"}},
    {Castille, Female, {"", "Луиза"}},
    {Castille, Female, {"", "Мария"}},
    {Castille, Female, {"", "Квитерия"}},
    {Castille, Female, {"", "Санча"}},
    {Castille, Female, {"", "Сюзанна"}},
    {Castille, Female, {"", "Урсула"}},
    {Castille, Female, {"", "Виоланта"}},
    {Eisen, Male, {"", "Адриан"}},
    {Eisen, Male, {"", "Бернард"}},
    {Eisen, Male, {"", "Дирк"}},
    {Eisen, Male, {"", "Эрих"}},
    {Eisen, Male, {"", "Густав"}},
    {Eisen, Male, {"", "Ханс"}},
    {Eisen, Male, {"", "Йозеф"}},
    {Eisen, Male, {"", "Курт"}},
    {Eisen, Male, {"", "Лоренц"}},
    {Eisen, Male, {"", "Макс"}},
    {Eisen, Male, {"", "Оливер"}},
    {Eisen, Male, {"", "Филипп"}},
    {Eisen, Male, {"", "Рейнхард"}},
    {Eisen, Male, {"", "Рольф"}},
    {Eisen, Male, {"", "Стефан"}},
    {Eisen, Male, {"", "Волькер"}},
    {Eisen, Male, {"", "Вензель"}},
    {Eisen, Male, {"", "Вилли"}},
    {Eisen, Male, {"", "Ксавьер"}},
    {Eisen, Male, {"", "Дитрих"}},
    {Eisen, Female, {"", "Барбара"}},
    {Eisen, Female, {"", "Конни"}},
    {Eisen, Female, {"", "Корнелия"}},
    {Eisen, Female, {"", "Диана"}},
    {Eisen, Female, {"", "Дора"}},
    {Eisen, Female, {"", "Эльза"}},
    {Eisen, Female, {"", "Ева"}},
    {Eisen, Female, {"", "Габриэль"}},
    {Eisen, Female, {"", "Ингрид"}},
    {Eisen, Female, {"", "Джессика"}},
    {Eisen, Female, {"", "Кирстин"}},
    {Eisen, Female, {"", "Рут"}},
    {Eisen, Female, {"", "Сигрид"}},
    {Eisen, Female, {"", "Сильвия"}},
    {Eisen, Female, {"", "Тина"}},
    {Eisen, Female, {"", "Хелэн"}},
    {Montaigne, Male, {"", "Амброуз"}},
    {Montaigne, Male, {"", "Блейз"}},
    {Montaigne, Male, {"", "Седрик"}},
    {Montaigne, Male, {"", "Даниэль"}},
    {Montaigne, Male, {"", "Жан"}},
    {Montaigne, Male, {"", "Феликс"}},
    {Montaigne, Male, {"", "Жерар"}},
    {Montaigne, Male, {"", "Гай"}},
    {Montaigne, Male, {"", "Генрих"}},
    {Montaigne, Male, {"", "Жак"}},
    {Montaigne, Male, {"", "Жюль"}},
    {Montaigne, Male, {"", "Люка"}},
    {Montaigne, Male, {"", "Марк"}},
    {Montaigne, Male, {"", "Николя"}},
    {Montaigne, Male, {"", "Пьер"}},
    {Montaigne, Male, {"", "Реми"}},
    {Montaigne, Male, {"", "Франсуа"}},
    {Montaigne, Female, {"", "Аллетта"}},
    {Montaigne, Female, {"", "Андре"}},
    {Montaigne, Female, {"", "Ариэль"}},
    {Montaigne, Female, {"", "Бланше"}},
    {Montaigne, Female, {"", "Камилла"}},
    {Montaigne, Female, {"", "Домини"}},
    {Montaigne, Female, {"", "Эстель"}},
    {Montaigne, Female, {"", "Франсина"}},
    {Montaigne, Female, {"", "Жоржетта"}},
    {Montaigne, Female, {"", "Генриетта"}},
    {Montaigne, Female, {"", "Ирен"}},
    {Montaigne, Female, {"", "Жюли"}},
    {Montaigne, Female, {"", "Лидия"}},
    {Montaigne, Female, {"", "Николь"}},
    {Montaigne, Female, {"", "Феба"}},
    {Montaigne, Female, {"", "Розелин"}},
    {Montaigne, Female, {"", "Сильвия"}},
    {Montaigne, Female, {"", "Вивьен"}},
    {Montaigne, Female, {"", "Франческа"}},
    {Ussura, Male, {"Alexey", "Алексей"}},
    {Ussura, Male, {"Alexander", "Александр"}},
    {Ussura, Male, {"Boris", "Борис"}},
    {Ussura, Male, {"Dmitriy", "Дмитрий"}},
    {Ussura, Male, {"Erema", "Ерема"}},
    {Ussura, Male, {"Fedor", "Федор"}},
    {Ussura, Male, {"Georgiy", "Георгий"}},
    {Ussura, Male, {"Ignatiy", "Игнатий"}},
    {Ussura, Male, {"Ilya", "Илья"}},
    {Ussura, Male, {"Michail", "Михаил"}},
    {Ussura, Male, {"Nikita", "Никита"}},
    {Ussura, Male, {"Petr", "Петр"}},
    {Ussura, Male, {"Sergey", "Сергей"}},
    {Ussura, Male, {"Timofei", "Тимофей"}},
    {Ussura, Male, {"Vasiliy", "Василий"}},
    {Ussura, Male, {"Vladimir", "Владимир"}},
    {Ussura, Male, {"Ivan", "Иван"}},
    {Ussura, Female, {"Afalia", "Афалия"}},
    {Ussura, Female, {"Anna", "Анна"}},
    {Ussura, Female, {"Bogdana", "Богдана"}},
    {Ussura, Female, {"Chenka", "Ченка"}},
    {Ussura, Female, {"Zoja", "Зоя"}},
    {Ussura, Female, {"Daria", "Дарья"}},
    {Ussura, Female, {"Elena", "Елена"}},
    {Ussura, Female, {"Galina", "Галина"}},
    {Ussura, Female, {"Irina", "Ирина"}},
    {Ussura, Female, {"Katherine", "Катерина"}},
    {Ussura, Female, {"Maria", "Мария"}},
    {Ussura, Female, {"Nana", "Нана"}},
    {Ussura, Female, {"Natalia", "Наталья"}},
    {Ussura, Female, {"Sofia", "Софья"}},
    {Ussura, Female, {"Tamara", "Тамара"}},
    {Ussura, Female, {"Inna", "Инна"}},
    {Vendel, Male, {"", "Альфгейр"}},
    {Vendel, Male, {"", "Браги"}},
    {Vendel, Male, {"", "Брон"}},
    {Vendel, Male, {"", "Эльдгрим"}},
    {Vendel, Male, {"", "Галлер"}},
    {Vendel, Male, {"", "Хаген"}},
    {Vendel, Male, {"", "Халльбйорн"}},
    {Vendel, Male, {"", "Храфн"}},
    {Vendel, Male, {"", "Йон"}},
    {Vendel, Male, {"", "Кетиль"}},
    {Vendel, Male, {"", "Магнус"}},
    {Vendel, Male, {"", "Ольвальд"}},
    {Vendel, Male, {"", "Рейн"}},
    {Vendel, Male, {"", "Серк"}},
    {Vendel, Male, {"", "Сигурд"}},
    {Vendel, Male, {"", "Сольмунд"}},
    {Vendel, Male, {"", "Торфин"}},
    {Vendel, Male, {"", "Транд"}},
    {Vendel, Male, {"", "Ульф"}},
    {Vendel, Male, {"", "Велейф"}},
    {Vendel, Female, {"", "Асгерд"}},
    {Vendel, Female, {"", "Асни"}},
    {Vendel, Female, {"", "Бера"}},
    {Vendel, Female, {"", "Далла"}},
    {Vendel, Female, {"", "Гроя"}},
    {Vendel, Female, {"", "Гудроид"}},
    {Vendel, Female, {"", "Храфнхильд"}},
    {Vendel, Female, {"", "Ингибйорг"}},
    {Vendel, Female, {"", "Йофрид"}},
    {Vendel, Female, {"", "Кадлин"}},
    {Vendel, Female, {"", "Льюфа"}},
    {Vendel, Female, {"", "Оск"}},
    {Vendel, Female, {"", "Раннвейг"}},
    {Vendel, Female, {"", "Сеун"}},
    {Vendel, Female, {"", "Сигрид"}},
    {Vendel, Female, {"", "Торхильд"}},
    {Vendel, Female, {"", "Ульфейд"}},
    {Vendel, Female, {"", "Вигдис"}},
    {Vendel, Female, {"", "Ингвильд"}},
    {Vendel, Female, {"", "Ир"}},
    {Vodacce, Male, {"", "Альберто"}},
    {Vodacce, Male, {"", "Антонио"}},
    {Vodacce, Male, {"", "Карло"}},
    {Vodacce, Male, {"", "Эрнесто"}},
    {Vodacce, Male, {"", "Фелис"}},
    {Vodacce, Male, {"", "Форутнато"}},
    {Vodacce, Male, {"", "Джианни"}},
    {Vodacce, Male, {"", "Джузеппе"}},
    {Vodacce, Male, {"", "Леон"}},
    {Vodacce, Male, {"", "Марко"}},
    {Vodacce, Male, {"", "Модесто"}},
    {Vodacce, Male, {"", "Педро"}},
    {Vodacce, Male, {"", "Ринальдо"}},
    {Vodacce, Male, {"", "Роландо"}},
    {Vodacce, Male, {"", "Савино"}},
    {Vodacce, Male, {"", "Сиро"}},
    {Vodacce, Male, {"", "Тимео"}},
    {Vodacce, Male, {"", "Тони"}},
    {Vodacce, Male, {"", "Умберто"}},
    {Vodacce, Male, {"", "Вито"}},
    {Vodacce, Female, {"", "Алезио"}},
    {Vodacce, Female, {"", "Ангелина"}},
    {Vodacce, Female, {"", "Кларисса"}},
    {Vodacce, Female, {"", "Кресченца"}},
    {Vodacce, Female, {"", "Елена"}},
    {Vodacce, Female, {"", "Фиора"}},
    {Vodacce, Female, {"", "Иоланда"}},
    {Vodacce, Female, {"", "Лея"}},
    {Vodacce, Female, {"", "Луиза"}},
    {Vodacce, Female, {"", "Миранда"}},
    {Vodacce, Female, {"", "Паола"}},
    {Vodacce, Female, {"", "Пенелопа"}},
    {Vodacce, Female, {"", "Рашель"}},
    {Vodacce, Female, {"", "Ребекка"}},
    {Vodacce, Female, {"", "Регина"}},
    {Vodacce, Female, {"", "Сандра"}},
    {Vodacce, Female, {"", "Валерия"}},
    {Vodacce, Female, {"", "Виола"}},
    {Vodacce, Female, {"", "Вероника"}},
};

//int get_random_name(tags nation, tags gender)
//{
//    int count = 0;
//    for(auto& e : objects)
//    {
//        if(e.nation==nation && e.gender==gender)
//            count++;
//    }
//    if(count)
//    {
//        count = rand()%count;
//        int index = 0;
//        for(auto& e : objects)
//        {
//            if(e.nation==nation && e.gender==gender)
//            {
//                if(count==0)
//                    return index;
//                count--;
//            }
//            index++;
//        }
//    }
//    return 0;
//}

short unsigned random(gender_s gender, nation_s* nation)
{
	short unsigned source[sizeof(name_data) / sizeof(name_data[0])];
	auto p = source;
	for(unsigned i = 0; i < sizeof(name_data) / sizeof(name_data[0]); i++)
	{
		if(name_data[i].gender != gender)
			continue;
		if(nation && name_data[i].nation != *nation)
			continue;
		*p++ = i;
	}
	auto count = p - source;
	if(!count)
		return 0xFFFF;
	return source[rand() % count];
}

//const char* game::getname(char* temp, int nation, int gender, int name, int family, int mother, int noble)
//{
//    temp[0] = 0;
//    switch(nation)
//    {
//    case Castille:
//        if(noble)
//        {
//            zcat(temp, szt("Don", "Дон"));
//            zcat(temp, " ");
//        }
//        zcat(temp, getnamepart(name));
//        if(mother)
//		{
//			zcat(temp, " ");
//			zcat(temp, bsgets(mother, Name));
//		}
//        if(family)
//		{
//			zcat(temp, szt(" de ", " де "));
//			zcat(temp, bsgets(family, Name));
//		}
//        break;
//    case Avalon:
//        if(noble)
//        {
//            if(gender==Female)
//                zcat(temp, szt("Ledi", "Леди"));
//            else
//                zcat(temp, szt("Lord", "Лорд"));
//            zcat(temp, " ");
//        }
//        zcat(temp, getnamepart(name));
//        if(family)
//		{
//			zcat(temp, " ");
//			zcat(temp, bsgets(family, Name));
//		}
//        break;
//	default:
//		zcat(temp, szt("Outsider","Чужестранец"));
//		break;
//    }
//    return temp;
//}

short unsigned hero::getnamerandom(gender_s gender, nation_s nation)
{
	auto r = random(gender, &nation);
	if(r != 0xFFFF)
		return r;
	return random(gender, 0);
}

const char* hero::getname(short unsigned id)
{
	return name_data[id].name[1];
}