//
// Created by Gchiko on 05-Dec-18.
//

#ifndef TAGGER_EXCEPTIONS_H
#define TAGGER_EXCEPTIONS_H

class not_found:public std::exception{};
class already_exists:public std::exception{};
class already_labeled:public std::exception{};
class not_labeled:public std::exception{};
class all_labeled:public std::exception{};

#endif //TAGGER_EXCEPTIONS_H
