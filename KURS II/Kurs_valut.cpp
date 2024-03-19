// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Header.h"

void KURSII::Kurs_valut::Check(int& day, int& month, const int year)
{
        if (month == 1) {
            day = 31;
            month = 12;
        }
        else if (month == 2) {
            day = 31;
            month = 1;
        }
        else if (month == 3 && year / 4 != 0) {
            day = 28;
            month = 2;
        }
        else if (month == 3 && year / 4 == 0) {
            day = 29;
            month = 2;
        }
        else if (month == 4) {
            day = 31;
            month = 3;
        }
        else if (month == 5) {
            day = 30;
            month = 4;
        }
        else if (month == 6) {
            day = 31;
            month = 5;
        }
        else if (month == 7) {
            day = 30;
            month = 6;
        }
        else if (month == 8) {
            day = 31;
            month = 7;
        }
        else if (month == 9) {
            day = 31;
            month = 8;
        }
        else if (month == 10) {
            day = 30;
            month = 9;
        }
        else if (month == 11) {
            day = 31;
            month = 10;
        }
        else if (month == 12) {
            day = 30;
            month = 11;
        }
}

void KURSII::Kurs_valut::A_Check(int& day, int& month, const int year) 
{
    if (month == 12 && day > 31) {
        day = 1;
        month = 1;
    }
    else if (month == 1 && day > 31) {
        day = 1;
        month = 2;
    }
    else if (month == 2 && year / 4 == 0 && day > 29) {
        day = 1;
        month = 3;
    }
    else if (month == 2 && year / 4 != 0 && day > 28) {
        day = 1;
        month = 3;
    }
    else if (month == 3 && day > 31) {
        day = 1;
        month = 4;
    }
    else if (month == 4 && day > 30) {
        day = 1;
        month = 5;
    }
    else if (month == 5 && day > 31) {
        day = 1;
        month = 6;
    }
    else if (month == 6 && day > 30) {
        day = 1;
        month = 7;
    }
    else if (month == 7 && day > 31) {
        day = 1;
        month = 8;
    }
    else if (month == 8 && day > 31) {
        day = 1;
        month = 9;
    }
    else if (month == 9 && day > 30) {
        day = 1;
        month = 10;
    }
    else if (month == 10 && day > 31) {
        day = 1;
        month = 11;
    }
    else if (month == 11 && day > 30) {
        day = 1;
        month = 12;
    }
}

void KURSII::Kurs_valut::Chislo(Regex^ regex, Match^ match, String^& now, String^& day, String^& month, String^& year)
{
    int da = System::Convert::ToInt32(day);
    int mon = System::Convert::ToInt32(month);
    int yea = System::Convert::ToInt32(year);

    WebClient^ wb = gcnew WebClient();
   
    
    if (comboBox2->Text == "������") {
        for (int i = 1; i < 10; i++) {
            da--;
            if (da < 1)
                Check(da, mon, yea); //�������� ���� �� ������������
        }

        if (comboBox1->Text == "USD") {
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01235");
            for (int i = 1; i < 9; i++) {
                da++;

                A_Check(da, mon, yea); // �������� ���� �� ������������
                
                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
            }
        }

        else if (comboBox1->Text == "EUR") { // ����� �������
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01239");
            for (int i = 1; i < 9; i++) {
                da++;

                A_Check(da, mon, yea); // �������� ���� �� ������������

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
            }
        }

        else if (comboBox1->Text == "KZT") { // ����� ������� 
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01335");
            for (int i = 1; i < 9; i++) {
                da++;

                A_Check(da, mon, yea); // �������� ���� �� ������������

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
            }
        }

        else if (comboBox1->Text == "UAH") { // ����� ������� 
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01720");
            for (int i = 1; i < 9; i++) {
                da++;

                A_Check(da, mon, yea); // �������� ���� �� ������������

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
            }
        }
    }

    else if (comboBox2->Text == "�����"){
        for (int i = 1; i < 30; i++) {
            da--;
            if (da < 1)
                Check(da, mon, yea); //�������� ���� �� ������������
        }

        if (comboBox1->Text == "USD") {
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01235");
            for (int i = 1; i < 29; i++) {
                da++;
                A_Check(da, mon, yea); // �������� ���� �� ������������

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
            }
        }

        else if (comboBox1->Text == "EUR") { // ����� �������
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01239");
            for (int i = 1; i < 30; i++) {
                da++;

                A_Check(da, mon, yea); // �������� ���� �� ������������

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
            }
        }

        else if (comboBox1->Text == "KZT") { // ����� ������� 
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01335");
            for (int i = 1; i < 30; i++) {
                da++;

                A_Check(da, mon, yea); // �������� ���� �� ������������

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea +"\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
            }
        }

        else if (comboBox1->Text == "UAH") { // ����� ������� 
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01720");
            for (int i = 1; i < 30; i++) {
                da++;

                A_Check(da, mon, yea); // �������� ���� �� ������������

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
            }
        }
    }

    else if (comboBox2->Text == "�������") {
        if (comboBox1->Text == "USD") {
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.04.2021&date_req2=" + now + "&VAL_NM_RQ=R01235");
            mon = mon - 3;
            for (int i = 1; i < 4; i++) {
                da = 2;

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }

                da = 15;

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
                mon++;
                if (mon > 12) {
                    mon = 1;
                    yea++;
                }
            }
            regex = gcnew Regex(now + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
            match = regex->Match(line);
            if (match->Groups[1]->Value != "") {
                y = System::Convert::ToDouble(match->Groups[1]->Value);
                this->chart2->Series[0]->Points->AddXY(now, y);
            }
        }

        else if (comboBox1->Text == "EUR") { // ����� �������
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01239");
            mon = mon - 3;
            for (int i = 1; i < 4; i++) {
                da = 2;

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
                    }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }

                da = 15;

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
                mon++;
                if (mon > 12) {
                    mon = 1;
                    yea++;

                }
            }
            regex = gcnew Regex(now + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
            match = regex->Match(line);
            if (match->Groups[1]->Value != "") {
                y = System::Convert::ToDouble(match->Groups[1]->Value);
                this->chart2->Series[0]->Points->AddXY(now, y);
            }
        }

        else if (comboBox1->Text == "KZT") { // ����� ������� 
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01335");
            mon = mon - 3;
            for (int i = 1; i < 4; i++) {
                da = 2;

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }

                da = 15;

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }
                mon++;
                if (mon > 12) {
                    mon = 1;
                    yea++;

                }
            }
            regex = gcnew Regex(now + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");
            match = regex->Match(line);
            if (match->Groups[1]->Value != "") {
                y = System::Convert::ToDouble(match->Groups[1]->Value);
                this->chart2->Series[0]->Points->AddXY(now, y);
            }
        }

        else if (comboBox1->Text == "UAH") { // ����� ������� 
            String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01720");
            mon = mon - 3;
            for (int i = 1; i < 4; i++) {
                da = 2;

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                }

                da = 15;

                if (mon < 10) {
                    regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");
                }
                else {
                    regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");

                }
                match = regex->Match(line);
                if (match->Groups[1]->Value != "") {
                    y = System::Convert::ToDouble(match->Groups[1]->Value);
                    this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
                } 
                mon++;
                if (mon > 12) {
                    mon = 1;
                    yea++;

                }
            }
            regex = gcnew Regex(now + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");
            match = regex->Match(line);
            if (match->Groups[1]->Value != "") {
                y = System::Convert::ToDouble(match->Groups[1]->Value);
                this->chart2->Series[0]->Points->AddXY(now, y);
            }
        }
    }

    else if (comboBox2->Text == "���") {
    if (comboBox1->Text == "USD") {
        String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.04.2021&date_req2=" + now + "&VAL_NM_RQ=R01235");
        yea--;
        for (int i = 1; i < 10; i++) {
            da = 2;

            if (mon < 10) {
                regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
            }
            else {
                regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

            }
            match = regex->Match(line);
            if (match->Groups[1]->Value != "") {
                y = System::Convert::ToDouble(match->Groups[1]->Value);
                this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
            }

            mon++;
            if (mon > 12) {
                mon = 1;
                yea++;
            }
        }
        regex = gcnew Regex(now + "\" Id=\"R01235\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
        match = regex->Match(line);
        if (match->Groups[1]->Value != "") {
            y = System::Convert::ToDouble(match->Groups[1]->Value);
            this->chart2->Series[0]->Points->AddXY(now, y);
        }
    }

    else if (comboBox1->Text == "EUR") { // ����� �������
        String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01239");
        yea--;
        for (int i = 1; i < 10; i++) {
            da = 2;

            if (mon < 10) {
                regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
            }
            else {
                regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");

            }
            match = regex->Match(line);
            if (match->Groups[1]->Value != "") {
                y = System::Convert::ToDouble(match->Groups[1]->Value);
                this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
            }

            mon++;
            if (mon > 12) {
                mon = 1;
                yea++;

            }
        }
        regex = gcnew Regex(now + "\" Id=\"R01239\"><Nominal>1</Nominal><Value>(.*?)</Value></Record>");
        match = regex->Match(line);
        if (match->Groups[1]->Value != "") {
            y = System::Convert::ToDouble(match->Groups[1]->Value);
            this->chart2->Series[0]->Points->AddXY(now, y);
        }
    }

    else if (comboBox1->Text == "KZT") { // ����� ������� 
        String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01335");
        yea--;
        for (int i = 1; i < 10; i++) {
            da = 2;

            if (mon < 10) {
                regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");
            }
            else {
                regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");

            }
            match = regex->Match(line);
            if (match->Groups[1]->Value != "") {
                y = System::Convert::ToDouble(match->Groups[1]->Value);
                this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
            }

            mon++;
            if (mon > 12) {
                mon = 1;
                yea++;

            }
        }
        regex = gcnew Regex(now + "\" Id=\"R01335\"><Nominal>100</Nominal><Value>(.*?)</Value></Record>");
        match = regex->Match(line);
        if (match->Groups[1]->Value != "") {
            y = System::Convert::ToDouble(match->Groups[1]->Value);
            this->chart2->Series[0]->Points->AddXY(now, y);
        }
    }

    else if (comboBox1->Text == "UAH") { // ����� ������� 
        String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_dynamic.asp?date_req1=24.07.2021&date_req2=" + now + "&VAL_NM_RQ=R01720");
        yea--;
        for (int i = 1; i < 10; i++) {
            da = 2;

            if (mon < 10) {
                regex = gcnew Regex(da + ".0" + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");
            }
            else {
                regex = gcnew Regex(da + "." + mon + "." + yea + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");

            }
            match = regex->Match(line);
            if (match->Groups[1]->Value != "") {
                y = System::Convert::ToDouble(match->Groups[1]->Value);
                this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, y);
            }

            mon++;
            if (mon > 12) {
                mon = 1;
                yea++;

            }
        }
        regex = gcnew Regex(now + "\" Id=\"R01720\"><Nominal>10</Nominal><Value>(.*?)</Value></Record>");
        match = regex->Match(line);
        if (match->Groups[1]->Value != "") {
            y = System::Convert::ToDouble(match->Groups[1]->Value);
            this->chart2->Series[0]->Points->AddXY(now, y);
        }
    }
    }
}


System::Void KURSII::Kurs_valut::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MessageBox::Show("1. �������� ������\n2. ������� ������ - �������", "����������");
}

System::Void KURSII::Kurs_valut::���������������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    MyForm^ form = gcnew MyForm();
    this->Hide();
    form->Show();
}

System::Void KURSII::Kurs_valut::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    Application::Exit();
}

System::Void KURSII::Kurs_valut::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
    this->chart2->Series[0]->Points->Clear();
    
    WebClient^ wb = gcnew WebClient();
    String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_daily.asp?");

    Regex^ regex0 = gcnew Regex("<ValCurs Date=\"(.*?)\" name");
    Match^ match0 = regex0->Match(line);

    String^ Today_data = match0->Groups[1]->Value;
    String^ day;
    String^ month;
    String^ year;

    for (int i = 0; i < 10; i++) {
        if (Today_data[i] != '.' && i < 3)
            day += Today_data[i];
        if (Today_data[i] != '.' && i > 2 && i < 5)
            month += Today_data[i];
        if (Today_data[i] != '.' && i > 5)
            year += Today_data[i];
    }
    Regex^ regex = gcnew Regex("<CharCode>" + comboBox1->Text + "</CharCode><Nominal>(.*?)</Nominal><Name>(.*?)</Name><Value>(.*?)</Value>");
    Match^ match = regex->Match(line);

    label3->Text = match->Groups[1]->Value + " " + comboBox1->Text + " = " + match->Groups[3]->Value + " RUB";
        
    Chislo(regex, match, Today_data, day, month, year);
   
    return System::Void();
}

System::Void KURSII::Kurs_valut::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
    Kurs_Data^ form = gcnew Kurs_Data();
    this->Hide();
    form->Show();
}
