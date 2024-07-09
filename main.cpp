#include "histogram.h"

int main(){
    size_t number_count;
    cerr << "Enter number count: \n";
    cin >> number_count;
    cerr << "Enter numbers \n";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin count \n";
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);

    //show_histogram_text(bins);
    show_histogram_svg(bins);
    
}