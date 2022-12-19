import weka.core.jvm as jwm
from weka.core.converters import Loader
from weka.classifiers import Classifier, Evaluation
from weka.filters import Filter
from weka.core.classes import Random

data_dir = "/home/oier/Universidad/DM/Weka Praktika/IK22/irteera/edge2/PHOGfilter.arff" # Best overall result with enhance 
#filter = "weka.filters.unsupervised.instance.imagefilter"

def main():
    
    jwm.start(packages="/home/oier/wekafiles/packages", max_heap_size="512m", system_info=True)
    loader = Loader(classname="weka.core.converters.ArffLoader")
    data = loader.load_file(data_dir) #Load the data base
    cls = Classifier(classname="weka.classifiers.trees.RandomForest")
    
    for index, inst in enumerate(data):
        pred = cls.classify_instance(inst)
        dist = cls.distribution_for_instance(inst)
        print(str(index+1) + ": label index=" + str(pred) + ", class distribution=" + str(dist))
    jwm.stop()

if __name__ == "__main__":
    main()