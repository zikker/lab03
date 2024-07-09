#include "histogram.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <algorithm>
void find_minmax(const vector<double> &numbers, double &min_el, double &max_el){
    min_el = *min_element(numbers.begin(), numbers.end());
    max_el = *max_element(numbers.begin(), numbers.end());
}


vector<double> input_numbers(size_t count){
    vector<double> result(count);
    for(int i = 0; i < count; i++){
        cin >> result[i];
    }
    return result;
}


vector<size_t> make_histogram(const vector<double> &numbers, size_t bin_count){
    double min_el, max_el;
    find_minmax(numbers, min_el, max_el);
    vector<size_t> bins(bin_count);
    double bin_size = (max_el - min_el) / bin_count;
    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min_el + j * bin_size;
            auto hi = min_el + (j + 1) * bin_size;
            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}


void show_histogram_text(const vector<size_t> &bins){
    double max_count = *max_element(bins.begin(), bins.end());
    const bool scaling_needed = max_count > MAX_ASTERISK;
    for(size_t bin : bins){
        if(bin < 10){
            cout << ' ';
        }
        if(bin < 100){
            cout << ' ';
        }
        cout << bin << '|';
        size_t height = bin;
        if(scaling_needed){
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_count);
        }
        
        for(int i = 0; i < height; i++){
            cout << '*';
        }
        cout << '\n';
    }
}


void svg_begin(double width, double height){
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}


void svg_end(){
    cout << "</svg>\n";
}


void show_histogram_svg(const vector<size_t>& bins){
    srand(time(0));
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    cerr << "Enter text decoration from list: 'none', 'underline', 'overline', 'line-through' \n";
    string decoration;
    cin >> decoration;
    while(!check_decoration(decoration)){
        cerr << "Enter decoration correctly \n";
        cin >> decoration;
    }
    double top = 0;
    double max_count = *max_element(bins.begin(), bins.end());
    for (size_t bin : bins) {
        const double bin_width = IMAGE_WIDTH * (static_cast<double>(bin) / max_count);
        string color = COLORS[rand() % 10];
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin), decoration);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, color, color);
        top += BIN_HEIGHT;
    }
    svg_end();
}


void svg_text(double left, double baseline, string text, string decoration){
    cout << "<text x='" << left << "' y='" << baseline << "' " << "text-decoration='" << decoration << "'" << ">" << text << "</text>";
}


void svg_rect(double x, double y, double width, double height, string stroke, string fill){
    cout << "<rect x='" << x << "' " <<  "y='" << y << "' " << "width='" << width << "' " <<  "height='" << height << "' ";
    cout << "stroke='" << stroke << "' " << "fill='" << fill << "'/>";
}


bool check_decoration(string decoration){
    if(decoration == "none" or decoration == "underline" or decoration == "overline" or decoration == "line-through"){
        return true;
    }
    else{
        return false;
    }
}


