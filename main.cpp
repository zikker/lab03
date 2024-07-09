#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
const auto IMAGE_WIDTH = 400;
const auto IMAGE_HEIGHT = 300;
const auto TEXT_LEFT = 20;
const auto TEXT_BASELINE = 20;
const auto TEXT_WIDTH = 50;
const auto BIN_HEIGHT = 30;
const auto BLOCK_WIDTH = 10;
vector<double> input_numbers(size_t count);
void find_minmax(const vector<double> &numbers, double &min_el, double &max_el);
vector<size_t> make_histogram(const vector<double> &numbers, size_t bin_count);
void show_histogram_text(const vector<size_t> &bins);
void svg_begin(double width, double height);
void svg_end();
void show_histogram_svg(const vector<size_t>& bins);
void svg_text(double left, double baseline, string text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");

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


vector<double> input_numbers(size_t count){
    vector<double> result(count);
    for(int i = 0; i < count; i++){
        cin >> result[i];
    }
    return result;
}


void find_minmax(const vector<double> &numbers, double &min_el, double &max_el){
    min_el = *min_element(numbers.begin(), numbers.end());
    max_el = *max_element(numbers.begin(), numbers.end());
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
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    svg_rect(0, 0, 100, 200);
    svg_end();
}


void svg_text(double left, double baseline, string text){
    cout << "<text x='" << left << "' y='" << baseline << "'" << ">" << text << "</text>";
}


void svg_rect(double x, double y, double width, double height, string stroke, string fill){
    cout << "<rect x='" << x << "' " <<  "y='" << y << "' " << "width='" << width << "' " <<  "height='" << height << "' ";
    cout << "stroke='" << stroke << "' " << "fill='" << fill << "'/>";
}