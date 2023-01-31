import weka.core.jvm as jwm
from weka.core.converters import Loader
from weka.classifiers import Classifier, Evaluation
from weka.filters import Filter
from weka.core.classes import Random

# Best overall result: Edge2 (PHOGFilter) 

def menu():
    
    data_dir = ""
    
    print("==== AUKERATU DAITEZKEEN DATU BASEAK ==== \n")
    print(" 1. | Edge2 - PHOGFilter             | \n")
    print(" 2. | Edge2 - EdgeHistogram          | \n")
    print(" 3. | Enhance - EdgeHistogram        | \n")
    print(" 4. | Enhance - SimpleColorHistogram | \n")
    
    while True:
        try:
            arff = input("Sartu ebaluatu nahi duzun datu baseari dagokion zenbakia: ")
            if int(arff) > 4 or int(arff) < 1:
                print("Saru duzun zenbakia ez da egokia, [1, 4] tartean egon behar da.\n")
            else:
                break
        except:
            print("Idatzi duzuna ez da zenbaki bat, mesedez zenbaki bat sartu")
            
    match arff:
        case '1':
            data_dir = "./Edge2 (.arff)/PHOGFilter.arff"
        case '2':
            data_dir = "./Edge2 (.arff)/EdgeHistogram.arff"
        case '3':
            data_dir = "./Enhance (.arff)/EdgeHistogram.arff"
        case '4': 
            data_dir = "./Enhance (.arff)/SimpleColorHistogram.arff"
    
    return data_dir

def main():
    
    data_dir = menu()
    
    jwm.start(packages="/home/oier/wekafiles/packages", max_heap_size="512m", system_info=True)
    loader = Loader(classname="weka.core.converters.ArffLoader")
    data = loader.load_file(data_dir) #Load the data base
    data.class_is_last()
    randomForest = Classifier(classname="weka.classifiers.trees.RandomForest")
    

    hit_rate = 0
    previous_hit_rate = 0
    variables_str = ""
    variable_list = []
    
    while previous_hit_rate >= hit_rate:
        hit_rate = previous_hit_rate
        max_hit_rate = 0
        
        print(variable_list)
        
        for index in range(1, data.num_attributes - 1):
            if index not in variable_list:
                
                print(str(index) + ", " + variables_str + "last")
                
                remove = Filter(classname="weka.filters.unsupervised.attribute.Remove", options=["-R", str(index)+"," + variables_str + ",last", "-V"])
                remove.inputformat(data)
                filtered_data = remove.filter(data)
                eval = Evaluation(filtered_data)
                eval.crossvalidate_model(randomForest, filtered_data, 10, Random(42))
                ratio = eval.percent_correct
                
                if ratio >= max_hit_rate:
                    max_hit_rate = ratio
                    variable = index
                print(ratio)
                
        variable_list.append(variable)
        previous_hit_rate = max_hit_rate
        variables_str = str(variable) + ", " + variables_str
                
    print(eval.summary())
            
    jwm.stop()

if __name__ == "__main__":
    main()