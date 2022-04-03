#ifndef AIRPLANE_H_INCLUDED
#define AIRPLANE_H_INCLUDED

enum class AirplaneType { Short, Medium, Long };

class Airplane {
    private:
        std::string m_name;
        AirplaneType m_type;
        float m_consumption;
        float m_fuel_capacity;
    public:
        // Constructors & Destructor
        Airplane() {}
        ~Airplane() {}

        // Getters
        std::string get_name() const { return m_name; }
        AirplaneType get_type() const { return m_type; }
        float get_consumption() const { return m_consumption; }
        float get_fuel_capacity() const { return m_fuel_capacity; }
        
        // Setters
        void set_name(std::string _name) { m_name = _name; }
        void set_type(AirplaneType _type) { m_type = _type; }
        void set_consumption(float _consumption) { m_consumption = _consumption; }
        void set_fuel_capacity(float _fuel_capacity) { m_fuel_capacity = _fuel_capacity; }

        // Methods
};

#endif // AIRPLANE_H_INCLUDED