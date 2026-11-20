#include <iostream>
#include <sil/sil.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <complex>
#include <array>

#include "random.hpp"

//algorithm pour utiliser std::sort

void green_only(sil::Image& image){
    for (glm::vec3& color : image.pixels()){  
    color.r = 0.f;
    color.b = 0.f;
    }
}

void echange_canaux(sil::Image& image){
    for (glm::vec3& color : image.pixels()){  
        std::swap(color.g, color.b);
    }
}

void gris(sil::Image& image){
    //gris = 0.2126 * r + 0.7152 * g + 0.0722 * b
    for (glm::vec3& color : image.pixels()){  
        color.r = color.b;
        color.g = color.b;
    }
}

void negatif(sil::Image& image){
    glm::vec3 const base{1, 1 ,1};
    for (glm::vec3& color : image.pixels()){  
        color = base - color;
    }
}

void degrade(){
    sil::Image image{300/*width*/, 200/*height*/};
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            image.pixel(x, y) = glm::vec3{ x/float(image.width()) };
        }
    }
    image.save("output/degrade.png");
}

void miroir(sil::Image& image){
    for (int x{0}; x < image.width()/2; x++){
        for (int y{0}; y < image.height(); y++){
            std::swap(image.pixel(x, y), image.pixel(image.width()-x-1, y)); //-1 car sinon x > width/2
        }
    }
}

void bruit(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        if(true_with_probability(0.3)){
            color = glm::vec3{random_float(0,1),random_float(0,1),random_float(0,1)};
        }
    }
}

void rota90(sil::Image& image){
    sil::Image new_image{image.height(), image.width()};
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            new_image.pixel(new_image.width()-y-1, x) = image.pixel(x, y);
        }
    }
    new_image.save("output/rota90.png");
}

void rgb_split(sil::Image& image){
    sil::Image new_image{image.width(),image.height()};
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if(x>=15 and x<=new_image.width()-15){
                new_image.pixel(x+15,y).r = image.pixel(x-15, y).r;
                new_image.pixel(x-15,y).b = image.pixel(x+15, y).b;
            }
            new_image.pixel(x, y).g = image.pixel(x, y).g;
        }
    }
    new_image.save("output/rgb_split.png");
}

void luminosite_assombrir(sil::Image& image){
    for (glm::vec3& color : image.pixels()){
        color *= color;
    }
}

void luminosite_eclaircir(sil::Image& image){
    //besoin d'importer cmath pour utiliser power.
    for (glm::vec3& color : image.pixels()){
        color.r = std::pow(color.r, 0.4f);
        color.g = std::pow(color.g, 0.4f);
        color.b = std::pow(color.b, 0.4f);
    }
}

void disque(sil::Image& image, int width=250, int height=250){ // ajout de coordonnées pour les exercices suivants (animation)
    //équation d'un disque de centre (0,0) : x² + y² <= R²
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if((x-width)*(x-width) + (y-height)*(y-height) <= 40*40){
                image.pixel(x,y) = glm::vec3{1};
            }
        }
    }
}

void cercle(sil::Image& image, int width=250, int height=250, int rayon=100){ // ajout de coordonnées pour les exercices suivants (rosace)
    //Remarque : Si on on applique seulement 40*40-thickness alors on obtient juste des petits points
    int thickness = 5;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            int position_relative = (x-width)*(x-width) + (y-height)*(y-height);
            if(position_relative <= rayon*rayon and position_relative >= (rayon-thickness)*(rayon-thickness)){
                image.pixel(x,y) = glm::vec3{1};
            }
        }
    }
}

void animation(){
    sil::Image image{500/*width*/, 500/*height*/};
    for(int i{0}; i <= image.width(); i+=50){
        sil::Image new_image{500/*width*/, 500/*height*/};
        disque(new_image);
        new_image.save("output/animation/image"+std::to_string(i)+".png");
    }
}

void rosace(sil::Image& image, int rayon, int nb_petale){
    int x{250};
    int y{250};
    cercle(image, x, y, rayon);
    for(int i{0}; i < nb_petale; i++){
        double angle{(2.0*M_PI / nb_petale) * i};
        int x_prime = x + rayon * std::cos(angle);
        int y_prime = y + rayon * std::sin(angle);
        cercle(image, x_prime, y_prime, rayon);
    }
}

void mosaique(sil::Image& image){
    sil::Image new_image{image.width()*5/*width*/, image.height()*5/*height*/};
    for(int x{0}; x<new_image.width(); x++){
        for(int y{0}; y<new_image.height(); y++){
            new_image.pixel(x, y) = image.pixel(x%image.width(), y%image.height());
        }
    }
    image = new_image;
}

void mosaique_miroir(sil::Image& image, int nb){
    sil::Image new_image{image.width()*nb/*width*/, image.height()*nb/*height*/};
    for(int x{0}; x<new_image.width(); x++){
        for(int y{0}; y<new_image.height(); y++){
            if((x/image.width())%2 == 0){
                new_image.pixel(x, y) = image.pixel(x%image.width(), y%image.height());
            }
            else{
                new_image.pixel(x, y) = image.pixel(image.width()-(x%image.width()+1), y%image.height());
            //     std::swap(new_image.pixel(x, y), image.pixel(image.width()-(x%image.width()+1), y%image.height()));
            }
        }
    }
    image = new_image;
}

void mosaique_miroir_fail(sil::Image& image, int nb){
    sil::Image new_image{image.width()*5/*width*/, image.height()*5/*height*/};
    for(int x{0}; x<new_image.width(); x++){
        for(int y{0}; y<new_image.height(); y++){
            if((x%image.width()/nb)%2 == 0){
                new_image.pixel(x, y) = image.pixel(x%image.width(), y%image.height());
            }
        }
    }
    image = new_image;
}

void glitch(sil::Image& image){
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            if(true_with_probability(0.0005)){
                int rectangle_x{random_int(5,60)};
                int rectangle_y{random_int(1,15)};
                int changement_x{random_int(0, image.width() - rectangle_x)};
                int changement_y{random_int(0, image.width() - rectangle_y)};
                if (x+rectangle_x <= image.width() and y+rectangle_y <= image.height()) {
                    for (int i{0}; i < rectangle_x; i++) {
                        for (int j{0}; j < rectangle_y; j++) {
                            std::swap(image.pixel(x + i, y + j), image.pixel(changement_x + i, changement_y + j));
                        }
                    }
                }
            }
        }
    }
}

void tri(sil::Image& image){
    sil::Image new_image{image.width()/*width*/, image.height()/*height*/};
    int taille{image.width()*image.height()};
    std::vector<glm::vec3> v(taille);
    int i{0};
    for (int y{0}; y < image.height(); y++){
        for (int x{0}; x < image.width(); x++){
            if(i <=taille){
                v[i] = image.pixel(x, y);
                i += 1;
            }
        }
    }
    std::sort(v.begin(), v.end(), [](glm::vec3 const& color1, glm::vec3 const& color2){
        return color1.b < color2.b;
    });
    for (int x{0}; x < new_image.width(); x++){
        for (int y{0}; y < new_image.height(); y++){
            new_image.pixel(x, y) = v[x+y*new_image.width()];
        }
    }
    new_image.save("output/tri.png");
}

void fractale(){
    sil::Image image{500/*width*/, 500/*height*/};
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            int i{0};
            std::complex<float> z{0.f, 0.f};
            while(i<=30 && std::abs(z) <= 2){
                std::complex<float> c{4*x/500.f-3.f, 4*y/500.f-2.f};
                z = z * z + c;
                i += 1;
            }
            if(std::abs(z) <= 2){
                image.pixel(x, y) = glm::vec3{1};
            }
            //gris = 0.2126 * r + 0.7152 * g + 0.0722 * b
            else{
                image.pixel(x,y) = glm::vec3{0};
            }
        }
    }
    image.save("output/fractale.png");
}

sil::Image resize(sil::Image& image, float scale){
    sil::Image new_image{static_cast<int>(image.width()*scale)/*width*/, static_cast<int>(image.height()*scale)/*height*/};
    for (int x{0}; x < new_image.width(); x++){
        for (int y{0}; y < new_image.height(); y++){
            new_image.pixel(x, y) = image.pixel(x/scale, y/scale);
        }
    }
    return new_image;
}

void convolution(sil::Image& image, std::array<std::array<float, 3>, 3> kernel){
    sil::Image new_image = image;
    for (int x{0}; x < image.width(); x++){
        for (int y{0}; y < image.height(); y++){
            glm::vec3 sum{0.f}; 
            int i{0};
            for (int distance_x{-1}; distance_x <= 1; distance_x++){
                for (int distance_y{-1}; distance_y <= 1; distance_y++){
                    int voisin_x = x + distance_x;
                    int voisin_y = y + distance_y;
                    if(voisin_x >= 0 && voisin_x < image.width() && voisin_y >= 0 && voisin_y < image.height()){
                        sum += image.pixel(voisin_x, voisin_y) * kernel[distance_y + 1][distance_x + 1];
                        i++;
                    }
                }
            }
            new_image.pixel(x, y) = sum;
        }
    }
    image = new_image;
}

int main()
{
    set_random_seed(1);

    // //EX1
    // {
    //     sil::Image image{"images/logo.png"};
    //     green_only(image);
    //     image.save("output/green_only.png");
    // }
    
    // //EX2
    // {
    //     sil::Image image{"images/logo.png"};
    //     echange_canaux(image);
    //     image.save("output/echange_canaux.png");
    // }

    // // //EX3
    // {
    //     sil::Image image{"images/logo.png"};
    //     gris(image);
    //     image.save("output/gris.png");
    // }

    // //EX4
    // {
    //     sil::Image image{"images/logo.png"};
    //     negatif(image);
    //     image.save("output/negatif.png");
    // }

    // //EX5
    // {
    //     degrade();
    // }

    // //EX6
    // {
    //     sil::Image image{"images/logo.png"};
    //     miroir(image);
    //     image.save("output/miroir.png");
    // }

    // //EX7
    // {
    //     sil::Image image{"images/logo.png"};
    //     bruit(image);
    //     image.save("output/bruit.png");
    // }

    // //EX8
    // {
    //     sil::Image image{"images/logo.png"};
    //     rota90(image);
    // }

    // //EX9
    // {
    //     sil::Image image{"images/logo.png"};
    //     rgb_split(image);
    // }
    
    // // //EX10 moins de lumière
    // {
    //     sil::Image image{"images/photo.jpg"};
    //     luminosite_assombrir(image);
    //     image.save("output/luminosite_assombrir.png");
    // }
    
    // //EX10 moins de lumière
    // {
    //     sil::Image image{"images/photo.jpg"};
    //     luminosite_eclaircir(image);
    //     image.save("output/luminosite_eclaircir.png");
    // }

    // //EX11
    // {
    //     sil::Image image{500/*width*/, 500/*height*/};
    //     disque(image);
    //     image.save("output/disque.png");
    // }
    
    // //EX12
    // {
    //     sil::Image image{500/*width*/, 500/*height*/};
    //     cercle(image);
    //     image.save("output/cercle.png");
    // }

    // //EX13
    // {
    //     //animation();
    // }

    // //EX14
    // {
    //     sil::Image image{500/*width*/, 500/*height*/};
    //     rosace(image, 100, 12);
    //     image.save("output/rosace.png");
    // }

    // //EX15
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaique(image);
    //     image.save("output/mosaique.png");
    // }

    //  //EX16_fails
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaique_miroir_fail(image, 4);
    //     image.save("output/mosaique_miroir_fail.png");
    // }

    //EX16
    {
        sil::Image image{"images/logo.png"};
        mosaique_miroir(image, 6);
        image.save("output/mosaique_miroir.png");
    }

    // //EX17
    // {
    //     sil::Image image{"images/logo.png"};
    //     glitch(image);
    //     image.save("output/glitch.png");
    // }

    // //EX18
    // {
    //     sil::Image image{"images/logo.png"};
    //     tri(image);
    // }

    // //EX19
    // {
    //     fractale();
    // }

    //EX20 blur
    {
        sil::Image image{"images/logo.png"};
        image = resize(image, 0.5);
        std::array<std::array<float, 3>, 3> kernel_blur{{
            {0.0625, 0.125, 0.0625},
            {0.125, 0.25, 0.125},
            {0.0625, 0.125, 0.0625}
        }};
        convolution(image, kernel_blur);
        image.save("output/convolution_blur.png");
    }

    //EX20.1 contour
    {
        sil::Image image{"images/logo.png"};
        std::array<std::array<float, 3>, 3> kernel_contour {{
            {-1.f, -1.f, -1.f},
            {-1.f,  8.f, -1.f},
            {-1.f, -1.f, -1.f}
        }};
        convolution(image, kernel_contour);
        image.save("output/convolution_contour.png");
    }

}