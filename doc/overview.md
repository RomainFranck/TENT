# TENT
## (Two Exponent N)-Tree
The goal of this project is to provide developers of software with lot of content (games, medical imagery, big data) with a way to store data with a compression tailored to their needs.
The data have to be indexable on n dimensions, like coordinates. The folding (compression) is two steps, the first one is applied during creation of the tent, the second one is optionnal and happens after the tree creation only if the data is not to be changed.
## How does it work ?
![alt text](https://github.com/RomainFranck/TENT/blob/master/doc/TENT.png)
A tent is just an aggregation of other tents and/or values plus some logic specific to the type of TENT, for exemple a DiscreteWaveletsTENT will store frequencies in all dimmensions instead of a TENT for each value, and a BigTENT can store noisy data more efficiently
## The Folding
The folding is the compression of the TENT, a fold is a predicate and a action, for each fold, the tent is tested for the predicate and the action is done accordingly, for example : if all children of a TENT have the same value, the value of the TENT is set and the children destroyed