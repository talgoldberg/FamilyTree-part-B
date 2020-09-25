//
// Created by tal goldberg.
//
#include "doctest.h"
#include "FamilyTree.hpp"
using namespace family;

#include <string>
using namespace std;



TEST_CASE("Tests for add mothers or add fathers and relation/find") {
Tree T("Avi");
T.addFather("Avi", "Gadi");
T.addMother("Avi", "Gila");
T.addFather("Gadi", "Ben");
T.addFather("Gila", "Dan");
T.addMother("Gadi", "Rina");
T.addMother("Gila", "Dina");
T.addFather("Ben", "Ron");
T.addMother("Ben", "Riki");
T.addFather("Rina", "Yosi");
T.addFather("Dan", "Eli");
T.addMother("Rina", "Mika");
T.addMother("Dan", "Ronit");
T.addFather("Dina", "Yosef");
T.addMother("Dina", "Zlil").addMother("Zlil", "Ziva").addMother("Ziva", "Yona");
CHECK(T.relation("Avi") == string("me"));
CHECK(T.relation("Gadi") == string("father"));
CHECK(T.relation("Ben") == string("grandfather"));
CHECK(T.relation("Dan") == string("grandfather"));
CHECK(T.relation("Dina") == string("grandmother"));
CHECK(T.relation("Rina") == string("grandmother"));
CHECK(T.relation("Ron") == string("great-grandfather"));
CHECK(T.relation("Riki") == string("great-grandmother"));
CHECK(T.relation("Yosi") == string("great-grandfather"));
CHECK(T.relation("Eli") == string("great-grandfather"));
CHECK(T.relation("Mika") == string("great-grandmother"));
CHECK(T.relation("Ronit") == string("great-grandmother"));
CHECK(T.relation("Gila") == string("mother"));
CHECK(T.relation("Yosef") == string("great-grandfather"));
CHECK(T.relation("Zlil") == string("great-grandmother"));
CHECK(T.relation("Ziva") == string("great-great-grandmother"));
CHECK(T.relation("Yona") == string("great-great-great-grandmother"));
CHECK(T.find("me") == string("Avi"));
CHECK(T.find("father") == string("Gadi"));
//     CHECK(T.find("grandfather") == string.containsAny("a", "b", "c");
// CHECK(T.find("grandfather") == string("Ben")||string("Dan"));
CHECK(T.find("mother") == string("Gila"));
//   CHECK(T.find("grandmother") == string("Rina")||string("Dina"));
CHECK(T.find("great-great-great-grandmother") == string("Yona"));
CHECK(T.find("great-great-grandmother") == string("Ziva"));
//  CHECK(T.find("great-grandmother") == string("Zlil")||string("Ronit")||string("Mika")||string("Riki"));
//  CHECK(T.find("great-grandfather") == string("Yosef")||string("Eli")||string("Yosi")||string("Ron"));
CHECK(T.relation("Tal") == string("unrelated"));
CHECK(T.relation("Avichai") == string("unrelated"));
CHECK(T.relation("Gigi") == string("unrelated"));
CHECK(T.relation("Didi") == string("unrelated"));
CHECK_THROWS(T.find("great-great-great-grandfather"));
CHECK_THROWS(T.find("great-great-grandfather"));
CHECK_THROWS(T.find("sister"));
CHECK_THROWS(T.find("brother"));
T.addFather("Eli", "Didi").addFather("Didi", "Gigi");
CHECK(T.find("great-great-grandfather") == string("Didi"));
CHECK(T.find("great-great-great-grandfather") == string("Gigi"));
CHECK(T.relation("Didi") == string("great-great-grandfather"));
CHECK(T.relation("Gigi") == string("great-great-great-grandfather"));
CHECK(T.relation("Tal") == string("unrelated"));
T.addFather("Eli", "Bibi");
T.addFather("Avi", "Michael");
CHECK(T.find("great-great-grandfather") == string("Didi"));
CHECK(T.find("great-great-great-grandfather") == string("Gigi"));
CHECK(T.find("father") == string("Gadi"));
CHECK(T.relation("Didi") == string("great-great-grandfather"));
CHECK(T.relation("Gigi") == string("great-great-great-grandfather"));
CHECK(T.relation("Michael") == string("unrelated"));

}

TEST_CASE("Tests for add mothers or add fathers and relation/find/remove") {
family::Tree T2("Avi");
T2.addFather("Avi", "Gadi")
.addMother("Avi", "Gila")
.addFather("Gadi", "Ben")
.addFather("Gila", "Dan")
.addMother("Gadi", "Rina")
.addMother("Gila", "Dina")
.addFather("Ben", "Ron")
.addMother("Ben", "Riki")
.addFather("Rina", "Yosi")
.addFather("Dan", "Eli")
.addMother("Rina", "Mika")
.addMother("Dan", "Ronit")
.addFather("Dina", "Yosef")
.addMother("Dina", "Zlil").addMother("Zlil", "Ziva").addMother("Ziva", "Yona");
CHECK(T2.relation("Natasha") == string("unrelated"));
CHECK(T2.relation("Thor") == string("unrelated"));
CHECK(T2.relation("Brus") == string("unrelated"));
CHECK(T2.relation("Avi") == string("me"));
CHECK(T2.relation("Gadi") == string("father"));
CHECK(T2.relation("Ben") == string("grandfather"));
CHECK(T2.relation("Dan") == string("grandfather"));
CHECK(T2.relation("Dina") == string("grandmother"));
CHECK(T2.relation("Rina") == string("grandmother"));
CHECK_THROWS(T2.remove("Avi"));
CHECK_THROWS(T2.remove("Dolores"));
CHECK_THROWS(T2.remove("Donatelo"));
T2.remove("Gadi");
CHECK(T2.relation("Gadi") == string("unrelated"));
CHECK_THROWS(T2.remove("Ben"));
CHECK_THROWS(T2.remove("Rina"));
CHECK_THROWS(T2.remove("Ron"));
CHECK(T2.relation("Rina") == string("unrelated"));
CHECK(T2.relation("Ben") == string("unrelated"));
CHECK(T2.relation("Dan") == string("grandfather"));
CHECK(T2.relation("Zlil") == string("great-grandmother"));
T2.remove("Zlil");
CHECK(T2.relation("Zlil") == string("unrelated"));

T2.addFather("Avi", "NewFather").addFather("NewFather", "Ben").addMother("NewFather", "Rina").addFather("Ben", "Ron")
.addMother("Ben", "Riki")
.addFather("Rina", "Yosi").addMother("Rina", "Mika");

CHECK(T2.relation("NewFather") == string("unrelated"));
CHECK_THROWS(T2.find("father"));
CHECK(T2.relation("Ben") == string("unrelated"));
CHECK(T2.relation("Rina") == string("unrelated"));
CHECK(T2.relation("Ron") == string("unrelated"));
CHECK(T2.relation("Riki") == string("unrelated"));
CHECK(T2.relation("Yosi") == string("unrelated"));
CHECK(T2.relation("Mika") == string("unrelated"));
CHECK(T2.relation("Ziva") == string("unrelated"));
CHECK(T2.relation("Yona") == string("unrelated")); //////////////////69

CHECK(T2.relation("Ziva") == string("unrelated"));
CHECK(T2.relation("Yona") == string("unrelated"));
CHECK_THROWS(T2.remove("Ziva"));
CHECK_THROWS(T2.remove("Yona"));
T2.addMother("Avi", "Or");
CHECK_THROWS(T2.remove("Or"));
CHECK(T2.find("mother") == string("Gila"));
CHECK(T2.relation("Gila") == string("mother"));
CHECK(T2.relation("Dan") == string("grandfather"));
CHECK(T2.relation("Dina") == string("grandmother"));

CHECK(T2.relation("Yosef") == string("great-grandfather"));
CHECK(T2.relation("Eli") == string("great-grandfather"));
CHECK(T2.relation("Ronit") == string("great-grandmother"));
CHECK_THROWS(T2.remove("Zlil"));
CHECK_THROWS(T2.remove("Dinaa"));
CHECK_THROWS(T2.remove("Milka"));
CHECK_THROWS(T2.remove("Or"));
CHECK_THROWS(T2.remove("aaa"));
CHECK_THROWS(T2.remove("bbb"));
CHECK(T2.relation("Or") == string("unrelated"));
CHECK(T2.relation("Avi") == string("me"));
CHECK_THROWS(T2.find("father"));
CHECK(T2.find("me") == string("Avi"));
CHECK_THROWS(T2.find("great-great-great-great-great-grandmother"));
CHECK_THROWS(T2.find("great-great-great-great-great-grandfather"));
CHECK_THROWS(T2.find("great-great-great-great-great-great-great-great-grandfather"));
CHECK_THROWS(T2.find("great-great-great-great-great-great-grandfather"));
CHECK_THROWS(T2.find("great-great-great-great-great-great-great-great-great-great-great-grandfather"));
CHECK_THROWS(T2.find("great-great-great-great-great-great-great-great-grandmother"));



}








