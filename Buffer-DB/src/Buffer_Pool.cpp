#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../include/BufferPool.h"
#include "../include/Frame.h"

using namespace std;

BufferPool::BufferPool() {
    this->numFrames = 0;
    this->capacity = 720;
    this->clock_pointer = 0;
}

BufferPool::BufferPool(int numFrames) {
    this->numFrames = numFrames;
    this->capacity = 720;
    this->clock_pointer = numFrames-1; // Inicializar el puntero del reloj
    

    for (int i = 0; i < this->numFrames; i++) {
        Frame frame(i);
        this->frames.push_back(frame);
        page_table[i] = -1;
         use_bits.push_back(false); // Inicializar los bits de uso
    }
}

vector<Frame> &BufferPool::getFrames() { return frames; }

Frame &BufferPool::getFrame(int frameID) {
    for (int i = 0; i < frames.size(); i++) {
        if (frames[i].getframeID() == frameID) {
            return frames[i];
        }
    }
    throw std::runtime_error("Frame not found");
}

void BufferPool::modifyPinInExistingFrame(int pageID, char flag) {
    for (int i = 0; i < frames.size(); i++) {
        if (page_table[frames[i].getframeID()] == pageID) {
            if (flag == 'i') {
                frames[i].incrementPinCount();
            } else if (flag == 'k' && frames[i].getPinCount() > 0) {
                frames[i].decrementPinCount();
            }
        }
    }
}

void BufferPool::setPage(Frame &frame, int frameID) {
    if (frameID >= 0 && frameID < numFrames) {
        frames[frameID] = frame;
        page_table[frameID] = 1;
    } else {
        cout << "SetP: Frame ID fuera de rango" << endl;
        return;
    }
    cout << "\nPagina [" << frameID << "] cargada correctamente." << endl;
}

void BufferPool::printPage(int frameID) {
    if (frameID >= 0 && frameID < numFrames) {
        if (page_table[frameID] == 1) {
            Frame &frame = frames[frameID];
            cout << "Frame ID: " << frameID << endl;
            cout << "Dirty Flag: " << "(frame.isDirty() ? \" true \" : \" false \")" << endl;
            cout << "Pin Count: " << "frame.getPinCount()" << endl;
            cout << "Page Capacity: " << "frame.getPage().getPageCapacity()" << endl;
            cout << "Page Content: " << "frame.getPage().getPageContent() " << endl;
        } else {
            cout << "Frame ID: " << frameID << " no contiene una página." << endl;
        }
    } else {
        cout << "Frame ID fuera de rango." << endl;
    }
}

void BufferPool::addRecord(int frameID, string record) {
    if (frameID >= 0 && frameID < numFrames) {
        if (page_table[frameID] == 1) {
            Frame &frame = frames[frameID];
            // frame.getPage().addRecord(record);
            cout << "Registro agregado correctamente." << endl;
        } else {
            cout << "Frame ID: " << frameID << " no contiene una página." << endl;
        }
    } else {
        cout << "Frame ID fuera de rango." << endl;
    }
}

void BufferPool::deleteRecord(int frameID, string record) {
    if (frameID >= 0 && frameID < numFrames) {
        if (page_table[frameID] == 1) {
            Frame &frame = frames[frameID];
            // frame.getPage().deleteRecord(record);
            cout << "Registro eliminado correctamente." << endl;
        } else {
            cout << "Frame ID: " << frameID << " no contiene una página." << endl;
        }
    } else {
        cout << "Frame ID fuera de rango." << endl;
    }
}

void BufferPool::pageIsDirty(int pageID) {
    if (pageID >= 0 && pageID < numFrames) {
        if (page_table[pageID] == 1) {
            Frame &frame = frames[pageID];
            // return frame.isDirty();
            return;
        } else {
            cout << "Frame ID: " << pageID << " no contiene una página." << endl;
            return;
        }
    } else {
        cout << "Frame ID fuera de rango." << endl;
        return;
    }
}

void BufferPool::freeFrame(int frameID) {
    if (frameID >= 0 && frameID < numFrames) {
        frames[frameID] = Frame(frameID);
        page_table[frameID] = -1;
        cout << "Frame [" << frameID << "] liberado correctamente." << endl;
    } else {
        cout << "Frame ID fuera de rango." << endl;
    }
}

int BufferPool::findFreeFrame() {
    for (auto it = page_table.begin(); it != page_table.end(); ++it) {
        if (it->second == -1) 
        {   
            use_bits[it->first] = true; // Marcar el bit de uso
            return it->first;
        }
    }

    /*Si retorna -2 es porque todos los frames ya tienen cargado una pagina*/
    return -2;
}

void BufferPool::setPageInFrame(int frameID, int pageID, Frame &frame) {
    if (frameID >= 0 && frameID < numFrames) {
        frames[frameID] = frame;
        page_table[frameID] = pageID;
    } else {
        cout << "SetP: Frame ID fuera de rango" << endl;
        return;
    }

    cout << "\nPagina [" << frameID << "] cargada Correctamente\n"
         << endl;
    //setHistory(pageID); // Guardar el historial de la página
}

bool BufferPool::isPageLoaded(int pageID) {
    for (const auto &pair : page_table) {
        if (pair.second == pageID) {
            use_bits[pair.first] = true;
            return true;
        }
    }
    return false;
}

int BufferPool::getFrameId(int pageID) {
    for (const auto &pair : page_table) {
        if (pair.second == pageID) {
            return pair.first;
        }
    }
    return -1;
}

void BufferPool::printTableFrame() {
    cout << setw(10) << "Frame Id" << "\t"
         << setw(10) << "Page Id" << "\t"
         << setw(10) << "Dirty Bit" << "\t"
         << setw(10) << "Pin Count" << "\t"
         << setw(10) << "Last Used" <<"\t" 
         << setw(10) << "bit" << endl;

    for (int i = 0; i < frames.size(); i++) {
        cout << setw(10) << frames[i].getframeID() << "\t"
             << setw(10) << frames[i].getPage().getPageId() << "\t"
             << setw(10) << (frames[i].isDirty() ? "Yes" : "No") << "\t"
             << setw(10) << frames[i].getPinCount() << "\t"
             << setw(10) << history[frames[i].getframeID()] << "\t"
             << setw(10) << use_bits[i] << endl;
    }

    
}

void BufferPool::setHistory(int pageID) {
    history[pageID] = 0;
}

void BufferPool::incrementHistory() {
    for (auto &pair : page_table) {
        if (pair.second != -1) history[pair.first]++;
    }
}

void BufferPool::LRU() {
    cout << "LRU" << endl;
    /*
    En el unordered_map history, se guardará el frameID y el tiempo en el que fue accedido. Atraves de las veces que se llame en general con +1.
    Ahora se buscara cual frame tiene mas tiempo en estar. Luego se revisara si el pin count esta en cero y ahi recien se llamara la funcion freeFrame.
    */
    int max = 0;
    int lastUsedFrame = 0;
    for (auto &pair : history) {
        if (pair.second > max) {
            max = pair.second;
            lastUsedFrame = pair.first;
        }
    }
    if (frames[lastUsedFrame].getPinCount() == 0) {
        history[lastUsedFrame] = 0;
        freeFrame(lastUsedFrame);
    } else {
        cout << "No se puede liberar el frame " << lastUsedFrame << " porque tiene un pin count mayor a 0" << endl;
    }
}

void BufferPool::Clock() {
    int iterations = 0; // Contador de iteraciones

    while (iterations <= numFrames) { // Limitar el número de iteraciones a numFrames
        cout << "----entrada---"<<clock_pointer<< "------------" << endl;
        
        if (!use_bits[clock_pointer] && frames[clock_pointer].getPinCount() == 0) {
            // Si el bit de uso es 0 y el pin count es 0, reemplazar este frame
            freeFrame(clock_pointer);
            clock_pointer = (clock_pointer == 0) ? numFrames - 1 : clock_pointer - 1;
            break;
        } else {
            cout<<use_bits[clock_pointer]<<endl;
            // Si el bit de uso es 1, ponerlo a 0 y avanzar el puntero
            use_bits[clock_pointer] = false;
            clock_pointer = (clock_pointer == 0) ? numFrames - 1 : clock_pointer - 1;
        }

        iterations++; // Incrementar el contador de iteraciones
    }

    // Si se inspeccionaron todos los frames y no se encontró ninguno para reemplazar
    if (iterations >= numFrames) {
        cout << "No se puede liberar ningún frame ya que todos están en uso." << endl;
        return;
    }
    cout << "--salida-----"<<clock_pointer<< "------------" << endl;
}

