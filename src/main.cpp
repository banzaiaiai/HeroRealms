#include "backEnd/Carte/Carte.hpp"
#include "backEnd/Effect/DamageEffect.hpp"
#include "backEnd/Effect/IEffect.hpp"
#include "backEnd/Joueur.hpp"
#include "backEnd/Partie.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
int main()
{
  // Création d'une carte qui ajoute 5 de dégat 
  Carte cDegat1 = Carte();
  std::shared_ptr<IEffect> seDegat1(new DamageEffect(5));
  std::vector<std::shared_ptr<IEffect>> vDegat1;
  vDegat1.push_back(seDegat1);
  cDegat1.addTrigger(OnPlay, vDegat1);


  // Création d'une partie
  std::vector<Carte> deck1 ;
  std::vector<Carte> deck2 ;
  for(int i=0;i<20;i++){
    deck1.push_back(cDegat1);
    deck2.push_back(cDegat1);
  }
  

  Partie partie1 = Partie(deck1);
  Joueur joueur1 = Joueur(0,partie1,"teste1",deck1);
  Joueur joueur2 = Joueur(1,partie1,"teste2",deck2);
  
  // début des teste 
  std::cout<<"Taille des decks" << joueur1.getPioche().size()<<" "<<joueur2.getPioche().size()<< "\n";
  std::cout<<"Taille des mains" << joueur1.getMain().size()<<" "<<joueur2.getMain().size()<< "\n";
  joueur1.piocher(1);
  std::cout<<"Taille des decks" << joueur1.getPioche().size()<<" "<<joueur2.getPioche().size()<< "\n";
  std::cout<<"Taille des mains" << joueur1.getMain().size()<<" "<<joueur2.getMain().size()<< "\n";
  std::cout<<"Taille de la riviére" << partie1.getRiviere().size()<<"\n";


  return 0;
}
