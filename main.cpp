#include "library2.h"
#include <assert.h>
#include <iostream>
using namespace std;


void Test_Init_And_Quit(){
    void* DS = Init(-1);
    assert(DS == nullptr);
    Quit(&DS);
    assert(DS == nullptr);
    DS = Init(4);
    assert(DS != nullptr);
    Quit(&DS);
    assert(DS == nullptr);
    //DS == Init(0) //WHAT SHOULD IT DO???????????????????????????
}

void Test_AddImage(){

    void* DS = Init(4);
    assert(DS != nullptr);

    assert(AddImage(DS, 0) == INVALID_INPUT);
    assert(AddImage(DS, -1) == INVALID_INPUT);
    assert(AddImage(nullptr, 2) == INVALID_INPUT);

    assert(AddImage(DS, 8) == SUCCESS);
    assert(AddImage(DS, 10) == SUCCESS);
    assert(AddImage(DS, 9) == SUCCESS);

    assert(AddImage(nullptr, 10) == INVALID_INPUT);

    assert(AddImage(DS, 8) == FAILURE);
    assert(AddImage(DS, 10) == FAILURE);
    assert(AddImage(DS, 9) == FAILURE);

    for (int i = 1; i < 7; ++i) {
        assert(AddImage(DS, i) == SUCCESS);
        assert(AddImage(DS, i) == FAILURE);
    }
    for (int i = 1; i < 7; ++i) {
        assert(AddImage(DS, i) == FAILURE);
    }

    Quit(&DS);
    assert(DS == nullptr);
}

void Test_DeleteImage(){
    void* DS = Init(4);
    assert(DS != nullptr);

    for (int i = 1; i < 10; ++i) {
        AddImage(DS, i);
    }

    assert(DeleteImage(DS, 0) == INVALID_INPUT);
    assert(DeleteImage(DS, -1) == INVALID_INPUT);
    assert(DeleteImage(nullptr, 2) == INVALID_INPUT);

    assert(DeleteImage(DS, 1) == SUCCESS);
    assert(DeleteImage(DS, 1) == FAILURE);
    assert(AddImage(DS, 1) == SUCCESS);
    assert(DeleteImage(DS, 1) == SUCCESS);
    assert(DeleteImage(DS, 1) == FAILURE);

    for (int j = 2; j < 10; ++j) {
        assert(DeleteImage(DS, j) == SUCCESS);
        assert(DeleteImage(DS, j) == FAILURE);
    }

    for (int j = 9; j > 0; --j) {
        assert(DeleteImage(DS, j) == FAILURE);
        assert(AddImage(DS, j) == SUCCESS);
    }
    assert(DeleteImage(nullptr, 2) == INVALID_INPUT);

    assert(DeleteImage(DS, 7) == SUCCESS);
    assert(DeleteImage(DS, 1) == SUCCESS);
    assert(DeleteImage(DS, 9) == SUCCESS);
    assert(DeleteImage(DS, 8) == SUCCESS);
    assert(DeleteImage(DS, 3) == SUCCESS);
    assert(DeleteImage(DS, 6) == SUCCESS);
    assert(DeleteImage(DS, 2) == SUCCESS);
    assert(DeleteImage(DS, 5) == SUCCESS);
    assert(DeleteImage(DS, 4) == SUCCESS);

    assert(DeleteImage(DS, 7) == FAILURE);
    assert(DeleteImage(DS, 1) == FAILURE);
    assert(DeleteImage(DS, 9) == FAILURE);
    assert(DeleteImage(DS, 8) == FAILURE);
    assert(DeleteImage(DS, 3) == FAILURE);
    assert(DeleteImage(DS, 6) == FAILURE);
    assert(DeleteImage(DS, 2) == FAILURE);
    assert(DeleteImage(DS, 5) == FAILURE);
    assert(DeleteImage(DS, 4) == FAILURE);

    Quit(&DS);
    assert(DS == nullptr);
}

void Test_AddLabel(){
    void* DS = Init(4);
    assert(DS != nullptr);

    assert(AddImage(DS, 8) == SUCCESS);
    assert(AddImage(DS, 10) == SUCCESS);
    assert(AddImage(DS, 9) == SUCCESS);

    assert(AddLabel(DS, 0, 2, 20) == INVALID_INPUT);
    assert(AddLabel(DS, 8, -1, 20) == INVALID_INPUT);
    assert(AddLabel(DS, 8, 4, 20) == INVALID_INPUT);
    assert(AddLabel(DS, 8, 2, 0) == INVALID_INPUT);
    assert(AddLabel(DS, 8, 2, -1) == INVALID_INPUT);
    assert(AddLabel(DS, 11, 2, -1) == INVALID_INPUT);
    assert(AddLabel(nullptr, 8, 2, 20) == INVALID_INPUT);

  //  cout<<"HERE------------11111111111111"<<endl;
    assert(AddLabel(DS, 8, 0, 10) == SUCCESS);
   // cout<<"HERE-----------2222222222222-"<<endl;
    assert(AddLabel(DS, 8, 1, 20) == SUCCESS);
  //  cout<<"HERE----------3333333333333--"<<endl;
    assert(AddLabel(DS, 8, 2, 30) == SUCCESS);
    assert(AddLabel(DS, 8, 3, 40) == SUCCESS);

    assert(AddLabel(DS, 8, 2, 20) == FAILURE);
    assert(AddLabel(DS, 8, 2, 30) == FAILURE);
    assert(AddLabel(DS, 11, 0, 100) == FAILURE);

    assert(AddLabel(DS, 9, 1, 0) == INVALID_INPUT);
    assert(AddLabel(DS, 9, 4, 100) == INVALID_INPUT);
    assert(AddLabel(DS, 9, 1, 100) == SUCCESS);
    assert(AddLabel(DS, 9, 1, 200) == FAILURE);

    for (int i = 0; i < 4; ++i) {
        assert(AddLabel(DS, 10, i, 999) == SUCCESS);
    }

    assert(DeleteImage(DS, 10) == SUCCESS);
    assert(AddLabel(DS, 10, 0, 999) == FAILURE);
    assert(AddImage(DS, 10) == SUCCESS);

    for (int i = 0; i < 4; ++i) {
        assert(AddLabel(DS, 10, i, 999) == SUCCESS);
    }

    Quit(&DS);
    assert(DS == nullptr);
}

void Test_GetLabel(){
    void* DS = Init(4);
    assert(DS != nullptr);

    int label = 100;

    assert(AddImage(DS, 8) == SUCCESS);
    assert(AddImage(DS, 10) == SUCCESS);
    assert(AddImage(DS, 9) == SUCCESS);

    assert(AddLabel(DS, 8, 1, 10) == SUCCESS);
    assert(AddLabel(DS, 8, 2, 20) == SUCCESS);

    assert(GetLabel(DS, 0, 1, &label) == INVALID_INPUT);
    assert(GetLabel(DS, 8, 1, nullptr) == INVALID_INPUT);
    assert(GetLabel(DS, 8, 4, &label) == INVALID_INPUT);
    assert(GetLabel(DS, 8, -1, &label) == INVALID_INPUT);
    assert(GetLabel(nullptr, 8, 1, &label) == INVALID_INPUT);
    assert(GetLabel(DS, 11, -1, &label) == INVALID_INPUT);
    assert(label == 100);

    assert(GetLabel(DS, 11, 1, &label) == FAILURE);
    assert(GetLabel(DS, 9, 1, &label) == FAILURE);
    assert(GetLabel(DS, 8, 0, &label) == FAILURE);
    assert(GetLabel(DS, 8, 3, &label) == FAILURE);
    assert(label == 100);

    assert(GetLabel(DS, 8, 1, &label) == SUCCESS);
    assert(label == 10);

    assert(DeleteImage(DS, 8) == SUCCESS);
    assert(GetLabel(DS, 8, 2, &label) == FAILURE);
    assert(label == 10);

    assert(AddImage(DS, 8) == SUCCESS);
    assert(GetLabel(DS, 8, 2, &label) == FAILURE);
    assert(AddLabel(DS, 8, 2, 20) == SUCCESS);
    assert(GetLabel(DS, 8, 2, &label) == SUCCESS);
    assert(label == 20);

    Quit(&DS);
    assert(DS == nullptr);
}

void Test_DeleteLabel(){
    void* DS = Init(4);
    assert(DS != nullptr);

    int label = 100;

    assert(AddImage(DS, 8) == SUCCESS);
    assert(AddImage(DS, 10) == SUCCESS);
    assert(AddImage(DS, 9) == SUCCESS);

    assert(AddLabel(DS, 8, 1, 10) == SUCCESS);
    assert(AddLabel(DS, 8, 2, 20) == SUCCESS);
    assert(AddLabel(DS, 8, 3, 30) == SUCCESS);

    assert(DeleteLabel(DS, 0, 1) == INVALID_INPUT);
    assert(DeleteLabel(DS, 8, 4) == INVALID_INPUT);
    assert(DeleteLabel(DS, 8, -1) == INVALID_INPUT);
    assert(DeleteLabel(DS, 11, -1) == INVALID_INPUT);
    assert(DeleteLabel(nullptr, 8, 1) == INVALID_INPUT);

    assert(DeleteLabel(DS, 11, 1) == FAILURE);
    assert(DeleteLabel(DS, 8, 0) == FAILURE);

    assert(DeleteLabel(DS, 8, 2) == SUCCESS);
    assert(DeleteLabel(DS, 8, 2) == FAILURE);
    assert(AddLabel(DS, 8, 2, 888) == SUCCESS);
    assert(DeleteLabel(DS, 8, 2) == SUCCESS);

    assert(GetLabel(DS, 8, 2, &label) == FAILURE);

    assert(AddLabel(DS, 8, 2, 999) == SUCCESS);
    assert(GetLabel(DS, 8, 2, &label) == SUCCESS);
    assert(label == 999);

    assert(DeleteImage(DS, 8) == SUCCESS);
    assert(DeleteLabel(DS, 8, 2) == FAILURE);

    Quit(&DS);
    assert(DS == nullptr);
}

void Test_GetAllUnLabeledSegments(){
    void* DS = Init(4);
    assert(DS != nullptr);

    int numOfSegments = 100;
    int* segments;

    assert(AddImage(DS, 8) == SUCCESS);
    assert(AddImage(DS, 10) == SUCCESS);
    assert(AddImage(DS, 9) == SUCCESS);
    assert(AddImage(DS, 7) == SUCCESS);

    assert(AddLabel(DS, 7, 0, 4) == SUCCESS);
    assert(AddLabel(DS, 7, 1, 44) == SUCCESS);
    assert(AddLabel(DS, 7, 2, 444) == SUCCESS);
    assert(AddLabel(DS, 7, 3, 4444) == SUCCESS);
    assert(AddLabel(DS, 8, 1, 10) == SUCCESS);
    assert(AddLabel(DS, 8, 2, 20) == SUCCESS);
    assert(AddLabel(DS, 8, 3, 30) == SUCCESS);
    assert(AddLabel(DS, 9, 0, 111) == SUCCESS);
    assert(AddLabel(DS, 9, 2, 222) == SUCCESS);

    assert(GetAllUnLabeledSegments(DS, 0, &segments, &numOfSegments) == INVALID_INPUT);
    assert(GetAllUnLabeledSegments(DS, 8, nullptr, &numOfSegments) == INVALID_INPUT);
    assert(GetAllUnLabeledSegments(DS, 8, &segments, nullptr) == INVALID_INPUT);
    assert(GetAllUnLabeledSegments(DS, 11, nullptr, &numOfSegments) == INVALID_INPUT);
    assert(GetAllUnLabeledSegments(DS, 11, &segments, nullptr) == INVALID_INPUT);
    assert(GetAllUnLabeledSegments(nullptr, 8, &segments, &numOfSegments) == INVALID_INPUT);

    assert(GetAllUnLabeledSegments(DS, 11, &segments, &numOfSegments) == FAILURE);
    assert(GetAllUnLabeledSegments(DS, 7, &segments, &numOfSegments) == FAILURE);
    assert(numOfSegments == 100);

    assert(GetAllUnLabeledSegments(DS, 8, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 1);
    cout << "your array contains:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << segments[i] << endl;
    }
    cout << "should be: 0" << endl;
    free(segments);

    assert(GetAllUnLabeledSegments(DS, 9, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 2);
    cout << "your array contains:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << segments[i] << endl;
    }
    cout << "should be: 1, 3 (not necessarily in that order)" << endl;
    free(segments);

    assert(GetAllUnLabeledSegments(DS, 10, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 4);
    cout << "your array contains:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << segments[i] << endl;
    }
    cout << "should be: 0, 1, 2, 3 (not necessarily in that order)" << endl;
    free(segments);

    assert(DeleteLabel(DS, 7, 1) == SUCCESS);
    assert(AddLabel(DS, 8, 0, 40) == SUCCESS);
    assert(DeleteLabel(DS, 9, 2) == SUCCESS);
    assert(AddLabel(DS, 9, 3, 222) == SUCCESS);
    assert(AddLabel(DS, 10, 3, 333) == SUCCESS);

    assert(GetAllUnLabeledSegments(DS, 7, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 1);
    cout << "your array contains:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << segments[i] << endl;
    }
    cout << "should be: 1" << endl;
    free(segments);

    assert(GetAllUnLabeledSegments(DS, 8, &segments, &numOfSegments) == FAILURE);
    assert(numOfSegments == 1);

    assert(GetAllUnLabeledSegments(DS, 9, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 2);
    cout << "your array contains:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << segments[i] << endl;
    }
    cout << "should be: 1, 2 (not necessarily in that order)" << endl;
    free(segments);

    assert(GetAllUnLabeledSegments(DS, 10, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 3);
    cout << "your array contains:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << segments[i] << endl;
    }
    cout << "should be: 0, 1, 2 (not necessarily in that order)" << endl;
    free(segments);

    assert(DeleteImage(DS, 8) == SUCCESS);
    assert(GetAllUnLabeledSegments(DS, 8, &segments, &numOfSegments) == FAILURE);
    assert(AddImage(DS, 8) == SUCCESS);
    assert(GetAllUnLabeledSegments(DS, 8, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 4);
    cout << "your array contains:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << segments[i] << endl;
    }
    cout << "should be: 0, 1, 2, 3 (not necessarily in that order)" << endl;
    free(segments);

    Quit(&DS);
    assert(DS == nullptr);
}

void Test_GetAllSegmentsByLabel(){
    void* DS = Init(4);
    assert(DS != nullptr);

    int numOfSegments = 100;
    int* images;
    int* segments;

    assert(AddImage(DS, 8) == SUCCESS);
    assert(AddImage(DS, 10) == SUCCESS);
    assert(AddImage(DS, 9) == SUCCESS);
    assert(AddImage(DS, 7) == SUCCESS);
    assert(AddImage(DS, 6) == SUCCESS);

    assert(AddLabel(DS, 7, 2, 555) == SUCCESS);
    assert(AddLabel(DS, 8, 0, 111) == SUCCESS);
    assert(AddLabel(DS, 8, 1, 222) == SUCCESS);
    assert(AddLabel(DS, 8, 2, 333) == SUCCESS);
    assert(AddLabel(DS, 8, 3, 444) == SUCCESS);
    assert(AddLabel(DS, 9, 0, 999) == SUCCESS);
    assert(AddLabel(DS, 9, 1, 111) == SUCCESS);
    assert(AddLabel(DS, 9, 3, 111) == SUCCESS);
    assert(AddLabel(DS, 10, 0, 111) == SUCCESS);
    assert(AddLabel(DS, 10, 1, 111) == SUCCESS);
    assert(AddLabel(DS, 10, 2, 111) == SUCCESS);
    assert(AddLabel(DS, 10, 3, 111) == SUCCESS);

    assert(GetAllSegmentsByLabel(DS, 0, &images, &segments, &numOfSegments) == INVALID_INPUT);
    assert(GetAllSegmentsByLabel(DS, 111, nullptr, &segments, &numOfSegments) == INVALID_INPUT);
    assert(GetAllSegmentsByLabel(DS, 111, &images, nullptr, &numOfSegments) == INVALID_INPUT);
    assert(GetAllSegmentsByLabel(DS, 111, &images, &segments, nullptr) == INVALID_INPUT);
    assert(GetAllSegmentsByLabel(nullptr, 111, &images, &segments, &numOfSegments) == INVALID_INPUT);

    assert(GetAllSegmentsByLabel(DS, 777, &images, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 0);
    assert(images == nullptr);
    assert(segments == nullptr);

    assert(GetAllSegmentsByLabel(DS, 111, &images, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 7);
    cout << "your arrays contain:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << images[i] << "||" << segments[i] << endl;
    }
    cout << "should be:" << endl;
    cout << "8||0" << endl;
    cout << "9||1" << endl;
    cout << "9||3" << endl;
    cout << "10||0" << endl;
    cout << "10||1" << endl;
    cout << "10||2" << endl;
    cout << "10||3" << endl;
    free(images);
    free(segments);

    assert(AddLabel(DS, 6, 3, 111) == SUCCESS);
    assert(DeleteImage(DS, 8) == SUCCESS);
    assert(DeleteLabel(DS, 9, 1) == SUCCESS);
    assert(DeleteLabel(DS, 10, 2) == SUCCESS);
    assert(AddLabel(DS, 10, 2, 222) == SUCCESS);

    assert(GetAllSegmentsByLabel(DS, 111, &images, &segments, &numOfSegments) == SUCCESS);
    assert(numOfSegments == 5);
    cout << "your arrays contain:" << endl;
    for (int i = 0; i < numOfSegments; ++i) {
        cout << images[i] << "||" << segments[i] << endl;
    }
    cout << "should be:" << endl;
    cout << "6||3" << endl;
    cout << "9||3" << endl;
    cout << "10||0" << endl;
    cout << "10||1" << endl;
    cout << "10||3" << endl;
    free(images);
    free(segments);

    Quit(&DS);
    assert(DS == nullptr);
}

void YourTests(){

}

int main(int argc, const char**argv) {

    cout << "Welcome!" << endl;
    cout << "These tests are for part 2 of the first wet homework of data structures." << endl;
    cout << "I hope you pass them! (unless you are Idan Raz), Good Luck." << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    cout << "Testing Init And Quit" << endl;
    Test_Init_And_Quit();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing AddImage" << endl;
    Test_AddImage();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing DeleteImage" << endl;
    Test_DeleteImage();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

 cout << "Testing AddLabel" << endl;
 Test_AddLabel();
 cout << "PASSED!!!" << endl;

 cout << "." << endl;
 cout << "." << endl;
 cout << "." << endl;

 cout << "Testing GetLabel" << endl;
 Test_GetLabel();
 cout << "PASSED!!!" << endl;

 cout << "." << endl;
 cout << "." << endl;
 cout << "." << endl;

 cout << "Testing DeleteLabel" << endl;
 Test_DeleteLabel();
 cout << "PASSED!!!" << endl;

 cout << "." << endl;
 cout << "." << endl;
 cout << "." << endl;

 cout << "Testing GetAllUnLabeledSegments" << endl;
 Test_GetAllUnLabeledSegments();
 cout << "PASSED!!! (unless the arrays were different...)" << endl;

 cout << "." << endl;
 cout << "." << endl;
 cout << "." << endl;

 cout << "Testing GetAllSegmentsByLabel" << endl;
 Test_GetAllSegmentsByLabel();
 cout << "PASSED!!! (unless the arrays were different...)" << endl;

 cout << "." << endl;
 cout << "." << endl;
 cout << "." << endl;
 cout << "." << endl;
 cout << "." << endl;

 cout << "you did it!" << endl;
 cout << "you ACTUALLY did it!" << endl;
 cout << "well, I guess you can go do SAFOT now..." << endl;

 cout << "." << endl;
 cout << "." << endl;
 cout << "." << endl;

 cout << "Oh! WAIT!, i almost forgot to tell you..." << endl;
 cout << "you should check for memory leaks on valgrind!" << endl;

 cout << "by the way, you can also add your own tests by using the "
          "YourTests function above :)" << endl;
 YourTests();

 cout <<
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

 cout << "Creator - Sagi Levanon" << endl;

    return 0;
}