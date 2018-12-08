//
// Created by elia on 05-Dec-18.
//

#include "Image.h"

Image::Image(int seg_num) {
    this->seg_num =seg_num;
}

Image::~Image() {}

void Image::add_label(int seg_id,int label) {
    if (this->segments[seg_id] != 0) {
        throw already_labeled();
    }
    this->segments[seg_id] = label;
    this->not_labeled_segments.removeByPointer(this->pointers[seg_id]);
    this->pointers[seg_id] = NULL;
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

    this->not_labeled_segments.insert(seg_id, seg_id, &this->pointers[seg_id]);
}
int* Image::get_all_unlabled_segments(int* numOfSegments) {}

int* Image::get_all_segments_by_label(int label) {

}

int Image::get_num_of_segments_by_label() {

}