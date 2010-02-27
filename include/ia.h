#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "joueur.hpp"
#include <limits>
#include <cstdlib>

template<TJoueur joueur_actuel, unsigned int profondeur>
class IAJoueurMinMax: public Joueur<joueur_actuel> {

	/**
	 * Le plateau actuel, conservé ici pour permettre de le modifier
	 * lors du traitement de l'arbre
	 */
	Plateau plateauActuel;

	unsigned int nbCalculs;

public:

	inline IAJoueurMinMax() {
		cout << "Construction d'un IA avec pour profondeur " << profondeur
				<< endl;
	}

	/**
	 * Méthode comptabilisant les points et applique un facteur en fonction de la situation.
	 */
	static inline int comptabiliserPoints(unsigned int& nbCasesLibreAvant,
			unsigned int& nbCasesLibreApres, unsigned int& nbCasesJoueur) {
		unsigned int facteur = 16;

		if (nbCasesLibreAvant > 0 && nbCasesLibreApres > 0) {
			// Cas à favoriser
			facteur = 32;
		}

		if ((nbCasesLibreAvant + nbCasesLibreApres + nbCasesJoueur) < 4) {
			// Cas défavorable
			//cout << "Pas assez de cases" << endl;
			facteur = 0;
		}

		unsigned int retValue = facteur * (nbCasesLibreAvant
				+ nbCasesLibreApres + nbCasesJoueur);
		nbCasesLibreAvant = nbCasesLibreApres = nbCasesJoueur = 0;
		return retValue;
	}

	/**
	 *
	 */
	template<bool ia>
	inline int calculScoreJoueur() {
		TCase caseJoueur = (TCase) joueur_actuel;
		if (!ia) {
			// Evaluation du score du joueur adverse
			caseJoueur = (TCase) this->getJoueurAdverse();
		}

		unsigned int nbPoints = 0;
		unsigned int scoreIntermediaire = 0;

		// EVALUATION DES CASES LIBRES

		// Boucle sur les colonnes
		for (unsigned int colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
			bool aCroiserAdversaire = false;
			unsigned int nbCasesLibre = 0;
			unsigned int nbCasesAMoi = 0;

			// Boucle sur les lignes (début en haut à droite du plateau)
			for (int ligne = Plateau::HAUTEUR - 1; ligne > 0; ligne--) {
				TCase caseActuelle = plateauActuel.get(ligne, colonne);
				if (caseActuelle == NONE) {
					// Case libre
					nbCasesLibre++;
				} else if (caseActuelle == caseJoueur) {
					// Case non libre
					if (!aCroiserAdversaire)
						// case appartenant au joueur évalué
						nbCasesAMoi++;
				} else {
					aCroiserAdversaire = true;
				}
			}
			if (nbCasesLibre + nbCasesAMoi >= 4) {
				scoreIntermediaire += nbCasesLibre * 8 + nbCasesAMoi * 16;
			}
		}

		// EVALUATION VERTICALE

		// Boucle sur les lignes (Début en bas à droite du plateau)
		for (int ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
			unsigned int nbCasesLibreAvant = 0;
			unsigned int nbCasesJoueur = 0;
			unsigned int nbCasesLibreApres = 0;

			// Boucle sur les colonnes
			for (int colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
				TCase caseActuelle = plateauActuel.get(ligne, colonne);
				// A qui appartient la case ?
				if (caseActuelle == caseJoueur) {
					// Appartient au joueur évalué
					nbCasesJoueur++;
				} else if (caseActuelle == NONE) {
					// Case vide
					if (nbCasesJoueur == 0) {
						// Premiere case
						nbCasesLibreAvant++;
					} else {
						nbCasesLibreApres++;
					}
				} else {
					// case joueur adverse
					scoreIntermediaire
							+= comptabiliserPoints(nbCasesLibreAvant,
									nbCasesLibreApres, nbCasesJoueur);
				}
			}
			scoreIntermediaire += comptabiliserPoints(nbCasesLibreAvant,
					nbCasesLibreApres, nbCasesJoueur);
		}

		// Boucle sur les lignes (Début en bas à droite du plateau)
		for (int colonne = 0 ; colonne < Plateau::LARGEUR ; colonne++) {
			unsigned int nbCasesLibreAvant = 0;
			unsigned int nbCasesJoueur = 0;
			unsigned int nbCasesLibreApres = 0;

			// Boucle sur les colonnes
			for (int ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
				TCase caseActuelle = plateauActuel.get(ligne, colonne);
				// A qui appartient la case ?
				if (caseActuelle == caseJoueur) {
					// Appartient au joueur évalué
					nbCasesJoueur++;
				} else if (caseActuelle == NONE) {
					// Case vide
					if (nbCasesJoueur == 0) {
						// Premiere case
						nbCasesLibreAvant++;
					} else {
						nbCasesLibreApres++;
					}
				} else {
					// case joueur adverse
					scoreIntermediaire
							+= comptabiliserPoints(nbCasesLibreAvant,
									nbCasesLibreApres, nbCasesJoueur);
				}
			}
			scoreIntermediaire += comptabiliserPoints(nbCasesLibreAvant,
					nbCasesLibreApres, nbCasesJoueur);
		}
		return scoreIntermediaire;
	}

	/**
	 *
	 */
	inline int calculScore() {
		nbCalculs++;

		int score = calculScoreJoueur<true> () - calculScoreJoueur<false> ();
		//out << "Le score est de " << score << endl;
		return score;
	}

	/**
	 *
	 */
	inline bool isPartieFinit(size_t ligne, size_t colonne, TCase case_) {
		if (plateauActuel.isPartieFinit()) {
			return true;
		}

		if (plateauActuel.aGagner(ligne, colonne, case_)) {
			return true;
		}

		return false;
	}

	/**
	 *
	 */
	inline size_t effectuerCoup() {

		nbCalculs = 0;
		size_t max_colonne = Plateau::LARGEUR;
		const int betaInitial = numeric_limits<int>::max();
		const int alphaInitial = -numeric_limits<int>::max();
		int alpha = alphaInitial;

		if (profondeur > 0 && !plateauActuel.isPartieFinit()) {
			for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
				if (plateauActuel.colonneJouable(colonne) == false) {
					//FA_cout << "La colonne " << colonne << "n'est pas jouable"	<< endl;
					continue;
				} else {
					//FA_cout << "La colonne " << colonne << " est jouable" << endl;
				}

				size_t ligne = plateauActuel.addToColumn(colonne,
						(TCase) joueur_actuel);
				int score_temp = 0;
				if (plateauActuel.aGagner(ligne, colonne, (TCase) joueur_actuel)) {
					score_temp = numeric_limits<int>::max();
				} else {
					score_temp = this->min(profondeur, alpha, betaInitial);
				}
				//FA_cout << "Col :  " << colonne << " Score :  " << score_temp	<< endl;
				if (alpha < score_temp) {
					max_colonne = colonne;
					alpha = score_temp;
					//FA_cout << "Modification de alpha " << alpha	<< " pour la colonne " << colonne << endl;
				}
				plateauActuel.supprimerCoup(colonne);
			}
		}
		plateauActuel.addToColumn(max_colonne, (TCase) joueur_actuel);
		//FA_cout << "On a fait " << nbCalculs	<< " evaluation de la grille - colonne : " << max_colonne << endl;
		return max_colonne;
	}

	/**
	 *
	 */
	int min(const unsigned int profondeurActuelle, const int alpha, int beta) {
		if (profondeurActuelle == 0) {
			int calculScoreResult = this->calculScore();
			return calculScoreResult;
		}

		for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
			if (!plateauActuel.colonneJouable(colonne)) {
				continue;
			}

			size_t ligne_actuelle = plateauActuel.addToColumn(colonne,
					(TCase) this->getJoueurAdverse());

			int scoreTemporaire;

			//Pour éviter un appel récursif inutil
			if (plateauActuel.isPartieFinit()) {
				scoreTemporaire = calculScore();
			} else if (plateauActuel.aGagner(ligne_actuelle, colonne,
					(TCase) this->getJoueurAdverse())) {
				scoreTemporaire = -numeric_limits<int>::max();
			} else {
				scoreTemporaire
						= this->max(profondeurActuelle - 1, alpha, beta);
			}

			plateauActuel.supprimerCoup(colonne);

			if (beta > scoreTemporaire) {
				beta = scoreTemporaire;
			}

			if (beta <= alpha) {
				return beta;
			}
		}
		return beta;
	}

	/**
	 *
	 */
	int max(unsigned int profondeurActuelle, int alpha, const int beta) {
		if (profondeurActuelle == 0) {
			int calculScoreResult = this->calculScore();
			return calculScoreResult;
		}

		for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
			if (!plateauActuel.colonneJouable(colonne)) {
				continue;
			}

			size_t ligne_actuelle = plateauActuel.addToColumn(colonne,
					(TCase) joueur_actuel);

			int scoreTemporaire;

			//Pour éviter un appel récursif inutil
			if (plateauActuel.isPartieFinit()) {
				scoreTemporaire = calculScore();
			} else if (plateauActuel.aGagner(ligne_actuelle, colonne,
					(TCase) joueur_actuel)) {
				scoreTemporaire = numeric_limits<int>::max();
			} else {
				scoreTemporaire = min(profondeurActuelle - 1, alpha, beta);
			}

			plateauActuel.supprimerCoup(colonne);

			if (alpha < scoreTemporaire) {
				alpha = scoreTemporaire;
			}

			if (beta <= alpha) {
				return alpha;
			}
		}
		//cout << "Retour de max " << alpha << endl;
		return alpha;
	}

	/**
	 *
	 */
	inline virtual void prendreEnCompteCoupAdversaire(size_t colonne) {
		plateauActuel.addToColumn(colonne, (TCase) inverseJoueur(joueur_actuel));
	}

	/**
	 *
	 */
	inline virtual const string getJoueurInformations() {
		string retValue = "";
		retValue += JeuxPuissanceQuatre::playerToString(joueur_actuel)
				+ " joueur de type IA profondeur ";
		retValue += (int) profondeur;
		return retValue;
	}

	/**
	 *
	 */
	inline Plateau getPlateau() {
		return plateauActuel;
	}
};

#endif // IA_H_INCLUDED
