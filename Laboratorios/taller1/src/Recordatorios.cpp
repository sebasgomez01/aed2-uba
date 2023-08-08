#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(int mes, int dia);
    int mes();
    int dia();
    void incrementar_dia();
    // Completar declaraciones funciones
    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif

  private:
    //Completar miembros internos
    int mes_;
    int dia_ ;

};

Fecha::Fecha(int mes, int dia): mes_(mes), dia_(dia) {}

int Fecha::mes() {
    return mes_;
}

int Fecha::dia() {
    return dia_;
}

ostream& operator<<(ostream& os, Fecha f) {
    os << "" << f.dia() << "/" << f.mes() << "" ;
    return os;
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    bool igual_mes = this->mes() == o.mes();
    return igual_dia && igual_mes;
}
#endif

void Fecha::incrementar_dia() {
    if((dias_en_mes(this->mes())) == 28 and this->dia() == 28) {
        this->mes_ = mes_ + 1;
        this->dia_ = 1;
    }
    else if(dias_en_mes(this->mes()) == 31 and this->dia() == 31) {
        this->mes_ = mes_ + 1;
        this->dia_ = 1;
    }
    else if(dias_en_mes(this->mes()) == 30 and this->dia() == 30) {
        this->mes_ = mes_ + 1;
        this->dia_ = 1;
    } else {
        this->dia_ = dia_ + 1;
    }

}

// Ejercicio 11, 12

// Clase Horario

class Horario {
public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator<(Horario h);

private:
    int hora_;
    int min_;

};

Horario::Horario(uint hora, uint min): hora_(hora), min_(min) {}

uint Horario::hora() {
    return hora_;
}

uint Horario::min() {
    return min_;
}

ostream& operator<<(ostream& os, Horario h) {
    os << "" << h.hora() << ":" << h.min() << "" ;
    return os;
}

bool Horario::operator<(Horario h2) {
    return (hora_ < h2.hora_)
    || (hora_ == h2.hora_ && min_ < h2.min_)
    || (hora_ < h2.hora_ && min_ < h2.min_);
}

// Ejercicio 13

// Clase Recordatorio

class Recordatorio {
    public:
        Recordatorio(Fecha fecha, Horario horario, string mensaje);
        Fecha fecha();
        Horario horario();
        string mensaje();

    private:
        Fecha fecha_;
        Horario horario_;
        string mensaje_;
};

Recordatorio::Recordatorio(Fecha fecha, Horario horario, std::string mensaje): fecha_(fecha), horario_(horario),
    mensaje_(mensaje) {}

Fecha Recordatorio::fecha() {
    return fecha_;
}

Horario Recordatorio::horario() {
    return horario_;
}

string Recordatorio::mensaje() {
    return mensaje_;
}

ostream& operator<<(ostream& os, Recordatorio r) {
    os << "" << r.mensaje() << " @ " << r.fecha() << " " << r.horario() << "";
    return os;
}

// Ejercicio 14

// Clase Agenda

class Agenda {
    public:
        Agenda(Fecha fecha_inicial);
        void agregar_recordatorio(Recordatorio rec);
        void incrementar_dia();
        list<Recordatorio> recordatorios_de_hoy();
        Fecha hoy();

    private:
        list<Recordatorio> recordatorios_;
        Fecha hoy_;
};

Agenda::Agenda(Fecha fecha_inicial): hoy_(fecha_inicial) {}

void Agenda::agregar_recordatorio(Recordatorio rec) {
    recordatorios_.push_back(rec);
}

void Agenda::incrementar_dia() {
    hoy_.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    list<Recordatorio> recordatorios_hoy;
    for(Recordatorio rec : recordatorios_) {
        if(rec.fecha() == hoy_) {
            recordatorios_hoy.push_back(rec);
        }
    }
    recordatorios_hoy.sort([](Recordatorio r1, Recordatorio r2) {
        if (r1.horario() < r2.horario()) return true;
        else if (r2.horario() < r1.horario()) return false;
        else return r1.mensaje() < r2.mensaje();
    });
    return recordatorios_hoy;
}

Fecha Agenda::hoy() {
    return hoy_;
}

ostream& operator<<(ostream& os, Agenda a) {
    os << a.hoy() << endl;
    os << "=====" << endl;
    for(Recordatorio rec : a.recordatorios_de_hoy()) {
        os << rec << endl;
    }
    return os;
}


