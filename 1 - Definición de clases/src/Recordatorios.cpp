#include <iostream>
#include <list>
#include <sstream>   

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
    
    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif

  private:
    int mes_;
    int dia_;
};

Fecha::Fecha(int mes, int dia) : mes_(mes), dia_(dia) {}

int Fecha::mes(){
  return mes_;
}

int Fecha::dia(){
  return dia_;
}

void Fecha::incrementar_dia(){
  if(dia_ == dias_en_mes(mes_))
  {
    mes_++;
    dia_= 1 ;
  }
  else
  {
    dia_++;
  }
}

ostream& operator<<(ostream& os, Fecha f) {
    os << f.dia() << "/" << f.mes();
    return os;
}

#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    bool igual_dia = this->dia() == o.dia();
    bool igual_mes = this->mes() == o.mes();
    
    if(igual_dia == true && igual_mes == true)
    {
      return true;
    }
    else
    {
      return false;
    } 
}
#endif



// Ejercicio 11, 12

class Horario{
  public:
    Horario(uint hora, uint min);
    uint hora();
    uint min();
    bool operator<(Horario h);
    #if EJ >= 9
    bool operator==(Horario h);
    #endif

  private:
    uint hora_;
    uint min_;
};

Horario::Horario(uint hora, uint min) : hora_(hora), min_(min) {}

uint Horario::hora(){
  return hora_;
}

uint Horario::min(){
  return min_;
}

ostream& operator<<(ostream& os, Horario h) {
    os << h.hora() << ":" << h.min();
    return os;
}

bool Horario::operator<(Horario h) {
  int hora = this->hora();
  int min = this->min();

  if(hora > h.hora())
  {
    return false;
  }

  if(hora < h.hora())
  {
    return true;
  }

  if(hora == h.hora())
  {
    if(min < h.min())
    {
      return true;
    }
    else if(min >= h.min())
    {
      return false;
    }
  }

  return true;
}

#if EJ >= 9
  bool Horario::operator==(Horario h) {
      bool igual_hora = this->hora() == h.hora();
      bool igual_min = this->min() == h.min();
      
      if(igual_min == true && igual_hora == true)
      {
        return true;
      }
      else
      {
        return false;
      } 
  }
#endif

// Ejercicio 13

class Recordatorio{
  public:
    Recordatorio(Fecha fecha, Horario horario, string mensaje);
    Fecha f();
    Horario h();
    string m();
    #if EJ >= 9
    bool operator==(Recordatorio r);
    #endif
  
  private:
    Fecha f_;
    Horario h_;
    string m_;
};

Recordatorio::Recordatorio(Fecha fecha, Horario horario, string mensaje) : f_(fecha), h_(horario), m_(mensaje) {}

Fecha Recordatorio::f()
{
  return f_;
}

Horario Recordatorio::h()
{
  return h_;
}

string Recordatorio::m()
{
  return m_;
}
#if EJ >= 9
  bool Recordatorio::operator==(Recordatorio r) {
      bool igual_fecha = this->f() == r.f();
      bool igual_hora = this->h() == r.h();
      bool igual_mensaje = this->m() == r.m();
      
      if(igual_fecha == true && igual_hora == true && igual_mensaje == true)
      {
        return true;
      }
      else
      {
        return false;
      } 
  }
#endif
ostream& operator<<(ostream& os, Recordatorio r) {
    os << r.m() << " @ " << r.f() << " " << r.h();
    return os;
}


// Ejercicio 14

class Agenda{
  public:
    Agenda(Fecha fecha_inicial);
    void agregar_recordatorio(Recordatorio rec);
    void incrementar_dia();
    list<Recordatorio> recordatorios_de_hoy();
    Fecha hoy();

  private:
    Fecha fechainicial_;
    list<Recordatorio> r_;
};

Agenda::Agenda(Fecha fecha_inicial) : fechainicial_(fecha_inicial) {}

void Agenda::agregar_recordatorio(Recordatorio rec)
{
  r_.push_back(rec);
}

void Agenda::incrementar_dia()
{
  fechainicial_.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy()
{
  list<Recordatorio> rdehoy;
  
  #if EJ >= 9
    for(auto & recordatorio : r_)
    {    
      if(recordatorio.f() == fechainicial_)
      {
        rdehoy.push_back(recordatorio);
      }
    }
  #endif
  return rdehoy;
}

Fecha Agenda::hoy()
{
  return fechainicial_;
}

ostream& operator<<(ostream& os, Agenda a) {
  
  stringstream recordatorios;  
  list<Recordatorio> ordenados = a.recordatorios_de_hoy();
  list<Recordatorio>::iterator it;
  list<Recordatorio>::iterator it2;
  
  for (it = ordenados.begin(); it!= ordenados.end(); ++it)
  {
    list<Recordatorio>::iterator min = it;
    
    for (it2 = it; it2!= ordenados.end(); ++it2)
    {
      Recordatorio r = *it2;
      Recordatorio rmin = *it;

      if(r.h() < rmin.h())
      {
        min = it2;
      }
    }
    
    std::swap(*it, *min);
  }


  for (auto v : ordenados)
        recordatorios << v << "\n";

  
  os << a.hoy() << "\n" << "=====" << "\n" << recordatorios.str();
  return os;
}