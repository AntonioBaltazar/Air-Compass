#ifndef AIRPORT_H_INCLUDED
#define AIRPORT_H_INCLUDED

struct GPS {
    double latitude;
    double longtitude;
};

class Airport {
    private:
        std::string m_name;
        GPS m_location;
        int m_nb_runway, m_nb_parking;
        float m_delay_parking_to_runway, m_delay_landing, m_delay_anticollision;
    public:
        // Constructors & Destructor
        Aiport() {}
        ~Airport() {}

        // Getters
        std::string get_name() const { return m_name; }
        GPS & get_location() { return m_location; }
        int get_nb_runway() const { return m_nb_runway; }
        int get_nb_parking() const { return m_nb_parking; }
        float get_delay_parking_to_runway() const { return m_delay_parking_to_runway; }
        float get_delay_landing() const { return m_delay_landing; }
        float get_delay_anticollision() const { return m_delay_anticollision; }

        // Setters
        void set_name(std::string _name) { m_name = _name; }
        void set_nb_runway(int _nb_runway) { m_nb_runway = _nb_runway; }
        void set_nb_parking(int _nb_parking) { m_nb_parking = _nb_parking; }
        void set_delay_parking_to_runway(float _delay_parking_to_runway) { m_delay_parking_to_runway = _delay_parking_to_runway; }
        void set_delay_landing(float _delay_landing) { m_delay_landing = _delay_landing; }
        void set_delay_anticollision(float _delay_anticollision) { m_delay_anticollision = _delay_anticollision; }
};

#endif // AIRPORT_H_INCLUDED