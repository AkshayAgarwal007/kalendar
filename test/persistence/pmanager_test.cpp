#include "pmanager_test.h"
#include <QDebug>

PManagerTest::PManagerTest()
{
    unsigned long timestamp = (unsigned long) time(NULL);
    string test("test");
    this->valid_event = new Event(0, test, test, test, timestamp, timestamp + 100);
    this->valid_event_2 = new Event(100, test, test, test, timestamp, timestamp + 100000);
    /* Invalid Events */
    this->noname_event = new Event(1, string(""), test, test, timestamp, timestamp + 100);
    this->invalid_time_event = new Event(1, test, test, test, timestamp, timestamp - 100);

}

PManagerTest::~PManagerTest() {
    delete this->valid_event;
    delete this->valid_event_2;
    delete this->noname_event;
    delete this->invalid_time_event;
}

void PManagerTest::test_all() {
    test_pmanager_remove_all();
    test_pmanager_add_event();
    test_pmanager_get_events_of_month();
    test_pmanager_remove_event();
}

void PManagerTest::test_pmanager_remove_all() {
    Test::print("test_pmanager_remove_all ");
    PManager pm;
    pm.remove_all() ? Test::print_green("passed\n") : Test::print_red("failed\n");
}

void PManagerTest::test_pmanager_add_event() {
    Test::print("test_pmanager_add_event ");
    PManager pm;
    if ((!(pm.add_event(this->noname_event))) &&
       (!(pm.add_event(this->invalid_time_event))) &&
       (pm.add_event(this->valid_event)))
           Test::print_green("passed\n");
    else
           Test::print_red("failed\n");
    pm.remove_all();
}

void PManagerTest::test_pmanager_get_events_of_month() {
    Test::print("test_pmanager_get_events_of_month ");
    bool ret = false;
    PManager pm;
    pm.add_event(this->valid_event);
    time_t timestamp = time(NULL);
    struct tm *current_time = localtime(&timestamp);
    list<Event*> events = pm.get_events_of_month(current_time->tm_mon + 1, current_time->tm_year + 1900); // tm_mon is from 0 to 11, we need to have 1 - 12
    if (!(events.empty())) {
        list<Event*>::iterator it = events.begin();
        ret = this->valid_event->equals(**it); // *it has type Event*
        delete *it;
    }
    ret ? Test::print_green("passed\n") : Test::print_red("failed\n");
    pm.remove_all();

}

void PManagerTest::test_pmanager_remove_event() {
    Test::print("test_pmanager_remove_event ");
    bool ret = false;
    PManager pm;
    pm.add_event(this->valid_event);
    pm.add_event(this->valid_event_2);
    pm.remove_event(this->valid_event);
    time_t timestamp = time(NULL);
    struct tm *current_time = localtime(&timestamp);
    list<Event*> events = pm.get_events_of_month(current_time->tm_mon + 1, current_time->tm_year + 1900);
    if (events.size() == 1) {
        list<Event*>::iterator it = events.begin();
        ret = this->valid_event_2->equals(**it); // *it has type Event*
        delete *it;
    }
    ret ? Test::print_green("passed\n") : Test::print_red("failed\n");
    pm.remove_all();
}
