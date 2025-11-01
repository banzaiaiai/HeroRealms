#include "backEnd/Carte/Champion.hpp"
#include "frontEnd/CarteGraphique.hpp"

CarteGraphique::CarteGraphique(float x, float y, float width, float height, const Carte* carteLogique)
    :  _isSelected(false) ,_carteLogique(carteLogique)
{
    if (_carteLogique) {
        std::cerr << "Texture de " << _carteLogique->getName() << " "
            << _carteLogique->getTexture().getSize().x << std::endl;

        _sprite.setTexture(_carteLogique->getTexture());
        _sprite.setPosition(x, y);

        // Mise à l’échelle pour correspondre à width/height demandés
        auto size = _sprite.getTexture()->getSize();
        _sprite.setScale(width / size.x, height / size.y);
    }
}


bool CarteGraphique::contains(const sf::Vector2f& point) const {
    return _sprite.getGlobalBounds().contains(point);
}

void CarteGraphique::setSelected(bool selected) {
    _isSelected = selected;
    // Tu peux changer la couleur du sprite si sélectionné
    if (selected)
        _sprite.setColor(sf::Color(255, 255, 150)); // léger surlignage
    else
        _sprite.setColor(sf::Color::White);
}

void CarteGraphique::draw(sf::RenderWindow& window) const {
    window.draw(_sprite);
}

void CarteGraphique::setPosition(float x, float y) {
    _sprite.setPosition(x, y);
}

sf::Vector2f CarteGraphique::getPosition() const {
    return _sprite.getPosition();
}

sf::Vector2f CarteGraphique::getSize() const {
    auto bounds = _sprite.getGlobalBounds();
    return { bounds.width, bounds.height };
}

void CarteGraphique::updateAppearance() {
    // _carteLogique est const Carte*
    const Champion* ch = dynamic_cast<const Champion*>(_carteLogique);
    if (ch) {
        // ch est un Champion réel -> appeler méthode du Champion
        if (!ch->getActiver()) {
            _sprite.setColor(sf::Color(150,150,150));
        } else {
            _sprite.setColor(sf::Color::White);
        }
    } else {
        // pas un champion : comportement par défaut
        _sprite.setColor(sf::Color::White);
    }
}
