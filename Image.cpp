//
// Created by elia on 05-Dec-18.
//

#include "Image.h"
using namespace std;
Image::Image(int seg_num): seg_num(seg_num),segments(new int[seg_num]),
        pointers(new void*[seg_num]){


    for (int i = 0; i <seg_num ; ++i) {
        void* pointer;
        this->segments[i]=0;
        not_labeled_segments.insert(i,i,&pointer);
        pointers[i]=pointer;
    }



}
Image:: Image(const Image &im) {
    this->seg_num=im.seg_num;
    this->pointers=new void*[im.seg_num];
    this->segments=new int[im.seg_num];
    for (int i = 0; i < im.seg_num; ++i) {
        this->segments[i]=im.segments[i];
        this->pointers[i]=im.pointers[i];
    }
    this->not_labeled_segments=im.not_labeled_segments;
}
Image::~Image() {

    delete[] segments;
    delete[] pointers;
}

void Image::add_label(int seg_id,int label) {
    if ((this->segments[seg_id]) != 0) {
        throw already_labeled();
    }
        //not_labeled_segments.print();

    this->not_labeled_segments.removeByPointer((this->pointers[seg_id]));
    this->pointers[seg_id] = NULL;
    this->segments[seg_id] = label;

}

int Image::get_label(int seg_id) {
    if (this->segments[seg_id] == 0) {
        throw not_labeled();
    }

    return this->segments[seg_id];
}

void Image::delete_label(int seg_id) {
    if (this->segments[seg_id] == 0) {
        throw not_labeled();
    }
    this->segments[seg_id] = 0;

    this->not_labeled_segments.insert(seg_id, seg_id,
            &this->pointers[seg_id]);
}

int* Image::get_all_unlabled_segments(int* numOfSegments) {

    int size_of_list=not_labeled_segments.getSize();
    *numOfSegments=size_of_list;

    if(size_of_list==0){
        throw all_labeled();
    }


    int* seg_array=(int*)malloc(sizeof(int)*size_of_list);
    not_labeled_segments.list_to_array_keys(seg_array);

    return seg_array;
}

int* Image::get_all_segments_by_label(int label) {

}

int Image::get_num_of_segments_by_label() {

}

Image& Image::operator=(const Image &im) {
    if(this!=&im){
        this->seg_num=seg_num;
        if(this->segments) {
            delete[] this->segments;
        }
        if(this->pointers) {
            delete[] this->pointers;
        }

        this->pointers=new void*[im.seg_num];
        this->segments=new int[im.seg_num];
        for (int i = 0; i < seg_num; ++i) {
            this->segments[i]=im.segments[i];
            this->pointers[i]=im.pointers[i];
        }
        this->not_labeled_segments=im.not_labeled_segments;
    }
    return *this;
}
