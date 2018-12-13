//
// Created by elia on 05-Dec-18.
//

#include "ImageTagger.h"

ImageTagger::ImageTagger(int seg_limit) : seg_limit(seg_limit) {}

ImageTagger::~ImageTagger() {
   Image** arr=images.tree_to_array();
   int size=images.getSize();
   for (int i = 0; i <size ; ++i) {
      delete (arr[i]);
   }

   delete[] arr;
}

void ImageTagger::add_image(int image_id) {
    try {

        Image *image;
        images.search(image_id, (void **) &image);

    } catch (not_found &cf) {

        Image *new_im = new Image(image_id, seg_limit);
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

int *ImageTagger::get_all_unlabled_segments(int image_id, int *numOfSegments) {
    Image* image;
    this->images.search(image_id,(void**)&image);
    return (image->get_all_unlabled_segments(numOfSegments));
}


int **ImageTagger::get_all_segments_by_label(int label, int *numOfSegments) {
    Image** images_array = this->images.tree_to_array();
    *numOfSegments = 0;

    int num_of_images = this->images.getSize();
    for(int i = 0; i < num_of_images; ++i) {
        int num_of_seg_image_i = images_array[i]->get_num_of_segments_by_label(label);
        *numOfSegments += num_of_seg_image_i;
    }

    if(*numOfSegments == 0) {
        delete[] images_array;
        return nullptr;
    }

    int* segments_by_label = (int*)malloc(sizeof(int)*(*numOfSegments));
    int* images_by_label = (int*)malloc(sizeof(int)*(*numOfSegments));
    if(segments_by_label == nullptr || images_by_label == nullptr) {
        delete[] images_array;
        throw bad_alloc();
    }

    int insert = 0;
    for(int i = 0; i < num_of_images; ++i) {
        int image_id = images_array[i]->get_id();
        int image_i_num_of_seg = images_array[i]->get_num_of_segments_by_label(label);
        int *image_i_seg_array = images_array[i]->get_all_segments_by_label(label);

        for (int j = 0; j < image_i_num_of_seg; ++j) {
            images_by_label[j + insert] = image_id;
            segments_by_label[j + insert] = image_i_seg_array[j];
        }

        delete[] image_i_seg_array;
        insert += image_i_num_of_seg;
    }

    delete[] images_array;
    int** arrays = new int*[2];
    arrays[0] = images_by_label;
    arrays[1] = segments_by_label;
    return arrays;
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
