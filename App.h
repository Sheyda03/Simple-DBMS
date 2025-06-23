#pragma once
#include <string>
#include "Invoker.h"
#include "Database.h"

/// \brief App class to handle all data in the application
class App 
{
public:
    /// \brief Default constructor
    App();

    /// \brief Disable copy constructor
    App(const App&) = delete;

    /// \brief Disable operator=
    App& operator = (const App&) = delete;

    /// \brief Destructor for App class
    ~App();

    /// \brief The main method which runs tills program ends
    void run();
private:
    Database* db; ///< database member
    Invoker* invoker; ///< invoker member
};
