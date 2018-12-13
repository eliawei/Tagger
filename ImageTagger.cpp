//
// Created by elia on 05-Dec-18.
//

#include "ImageTagger.h"

ImageTagger::ImageTagger(int seg_limit) : seg_limit(seg_limit) {}

ImageTagger::~ImageTagger() {}

void ImageTagger::add_image(int image_id) {
    try {

        Image *image;
        images.search(image_id, (void **) &image);

    } catch (not_found &cf) {

        Image *new_im = new Image(seg_limit);
        void *p;
        images.insert(image_id, new_im, &p);
        return;

    }

    throw already_exists();
}

void ImageTagger::delete_image(int image_id) {
    images.remove_by_key(image_id);
}

void ImageTagger::add_label(int image_id, int seg_id, int label) {

    Image *image;
    this->images.search(image_id, (void **) &image);
    image->add_label(seg_id, label);

}

int ImageTagger::get_label(int image_id, int seg_id) {

    Image *image;
    this->images.search(image_id, (void **) &image);
    return image->get_label(seg_id);

}

void ImageTagger::delete_label(int image_id, int seg_id) {
    Image* image;
    this->images.search(image_id,(void**)&image);
    image->delete_label(seg_id);
}

int *ImageTagger::get_all_unlabled_segments(int image_id, int *numOfSegments) {}

int *ImageTagger::get_all_segments_by_label(int label, int *numOfSegments) {
    Image** images_array = this->images.tree_to_array();

    int num_of_images = this->images.getSize();
    for(int i = 0; i < num_of_images; ++i) {
        int num_of_seg_image_i = images_array[i]->get_num_of_segments_by_label(label);
        *numOfSegments += (num_of_seg_image_i * 2);
    }

    if(*numOfSegments == 0) {
        return NULL;
    }

    int* segments_by_label = (int*)malloc(*numOfSegments);
    if(segments_by_label == NULL) {
        throw bad_alloc();
    }

    int insert = 0;
    for(int i = 0; i < num_of_images; ++i) {
        int image_i_num_of_seg = images_array[i]->get_num_of_segments_by_label(label);
        int *image_i_seg_array = images_array[i]->get_all_segments_by_label(label);

        for (int i = 0; i < image_i_num_of_seg; ++i) {
            segments_by_label[i + insert] = i;
            segments_by_label[*numOfSegments + i + insert] = image_i_seg_array[i];
        }

        insert += image_i_num_of_seg;
    }

    return segments_by_label;
}

ImageTagger::ImageTagger(const ImageTagger &it) {
    this->seg_limit = it.seg_limit;
    this->images = it.images;
}

ImageTagger &ImageTagger::operator=(const ImageTagger &it) {
    if (&it != this) {
        seg_limit = it.seg_limit;
        this->images = it.images;
    }
    return *this;
}
