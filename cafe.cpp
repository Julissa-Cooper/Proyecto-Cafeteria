#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

const int NUM_PRODUCTOS = 20;
const int MAX_CARRITO = 50;
const int PIN_EMPLEADO = 2007;

// DATOS DE LOS PRODUCTOS
string nombres[NUM_PRODUCTOS] = {
    "Hamburguesa", "Pizza", "Hot Dog", "Pupusas",
    "Panini de pollo",
    "Papas fritas", "Ensalada", "Pan con Ajo",
    "Agua", "Refresco", "Jugo", "Coca-Cola",
    "Te frio", "Cafe", "Frozen", "Licuado",
    "Pastel", "Helado", "Brownie", "Galletas"
};

double precios[NUM_PRODUCTOS] = {
    3.50, 5.00, 2.50, 1.00, 4.50,
    1.50, 2.00, 1.00,
    1.00, 2.00, 2.50, 1.00, 1.00, 1.50, 2.50, 2.00,
    3.00, 2.00, 1.50, 1.00
};

int stock[NUM_PRODUCTOS] = {
    20, 15, 20, 30, 15,
    25, 20, 20,
    50, 30, 30, 40, 30, 50, 20, 20,
    15, 20, 15, 30
};

int carritoProd[MAX_CARRITO];
int carritoCant[MAX_CARRITO];

double ventasTotalesDia = 0;
int totalTransacciones = 0;
int unidadesVendidas[NUM_PRODUCTOS] = {0};
int numeroTicket = 100;

// FUNCIONES PARA LEER DATOS

void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerEntero(string mensaje) {
    int valor;

    while (true) {
        cout << mensaje;

        if (cin >> valor) {
            return valor;
        }

        cout << "Entrada invalida. Ingrese un numero entero.\n";
        limpiarEntrada();
    }
}

double leerDouble(string mensaje) {
    double valor;

    while (true) {
        cout << mensaje;

        if (cin >> valor) {
            return valor;
        }

        cout << "Entrada invalida. Ingrese un numero.\n";
        limpiarEntrada();
    }
}

// FUNCION PARA MOSTRAR EL MENU PRINCIPAL

void mostrarMenu() {
    cout << "\n====================================\n";
    cout << "         MENU PARA ORDENAR\n";
    cout << "====================================\n";

    cout << "\n--- PLATILLOS ---\n";

    for (int i = 0; i < 5; i++) {
        cout << i + 1 << ". " << nombres[i]
             << " - $" << precios[i] << endl;
    }

    cout << "\n--- ENTRADAS ---\n";

    for (int i = 5; i < 8; i++) {
        cout << i + 1 << ". " << nombres[i]
             << " - $" << precios[i] << endl;
    }

    cout << "\n--- BEBIDAS ---\n";

    for (int i = 8; i < 16; i++) {
        cout << i + 1 << ". " << nombres[i]
             << " - $" << precios[i] << endl;
    }

    cout << "\n--- POSTRES ---\n";

    for (int i = 16; i < 20; i++) {
        cout << i + 1 << ". " << nombres[i]
             << " - $" << precios[i] << endl;
    }

    cout << "\n====================================\n";
}

// FUNCION PARA MOSTRAR EL CATALOGO CON STOCK

void mostrarCatalogo() {
    cout << "\n--- CATALOGO Y EXISTENCIAS ---\n";

    for (int i = 0; i < NUM_PRODUCTOS; i++) {
        cout << i + 1 << ". " << nombres[i]
             << " - $" << precios[i]
             << " (Stock: " << stock[i] << ")\n";
    }
}

// FUNCION PARA GENERAR LA FACTURA

void generarFactura(
    string nombre,
    int mesa,
    string tipoVenta,
    string empleado,
    int itemsCarrito,
    double subtotal,
    double descEstudiante,
    double descVolumen,
    double iva,
    double totalPagar,
    double efectivo,
    double cambio,
    int metodoPago
) {
    numeroTicket++;

    ofstream factura("factura.txt");

    cout << fixed << setprecision(2);

    cout << "\n";
    cout << "========================================\n";
    cout << "          FACTURA DEL RESTAURANTE\n";
    cout << "========================================\n";

    cout << "Ticket: #" << numeroTicket << endl;
    cout << "Cliente: " << nombre << endl;
    cout << "Numero de mesa: " << mesa << endl;
    cout << "Tipo de venta: " << tipoVenta << endl;

    if (tipoVenta == "empleado") {
        cout << "Empleado: " << empleado << endl;
    }

    cout << "----------------------------------------\n";
    cout << "PRODUCTO          CANT.       TOTAL\n";
    cout << "----------------------------------------\n";

    if (factura.is_open()) {
        factura << fixed << setprecision(2);

        factura << "========================================\n";
        factura << "          FACTURA DEL RESTAURANTE\n";
        factura << "========================================\n";

        factura << "Ticket: #" << numeroTicket << endl;
        factura << "Cliente: " << nombre << endl;
        factura << "Numero de mesa: " << mesa << endl;
        factura << "Tipo de venta: " << tipoVenta << endl;

        if (tipoVenta == "empleado") {
            factura << "Empleado: " << empleado << endl;
        }

        factura << "----------------------------------------\n";

        for (int i = 0; i < itemsCarrito; i++) {
            int idx = carritoProd[i];
            int cant = carritoCant[i];
            double importe = precios[idx] * cant;

            cout << nombres[idx] << " x" << cant
                 << "          $" << importe << endl;

            factura << nombres[idx] << " x" << cant
                    << "          $" << importe << endl;
        }

        factura << "----------------------------------------\n";
        factura << "Subtotal: $" << subtotal << endl;
        factura << "Descuento estudiante: -$" << descEstudiante << endl;
        factura << "Descuento volumen: -$" << descVolumen << endl;
        factura << "IVA (13%): $" << iva << endl;
        factura << "TOTAL PAGADO: $" << totalPagar << endl;

        if (metodoPago == 1) {
            factura << "Metodo de pago: Efectivo\n";
            factura << "Efectivo recibido: $" << efectivo << endl;
            factura << "Cambio: $" << cambio << endl;
        } else {
            factura << "Metodo de pago: Tarjeta\n";
        }

        factura << "========================================\n";
        factura << "       GRACIAS POR SU PREFERENCIA\n";
        factura << "========================================\n";

        factura.close();
    }

    cout << "----------------------------------------\n";
    cout << "Subtotal:               $" << subtotal << endl;
    cout << "Descuento estudiante:  -$" << descEstudiante << endl;
    cout << "Descuento volumen:     -$" << descVolumen << endl;
    cout << "IVA (13%):              $" << iva << endl;
    cout << "========================================\n";
    cout << "TOTAL A PAGAR:          $" << totalPagar << endl;

    if (metodoPago == 1) {
        cout << "Metodo de pago: Efectivo\n";
        cout << "Efectivo recibido: $" << efectivo << endl;
        cout << "Cambio: $" << cambio << endl;
    } else {
        cout << "Metodo de pago: Tarjeta\n";
    }

    cout << "========================================\n";
    cout << "       GRACIAS POR SU PREFERENCIA\n";
    cout << "========================================\n";

    cout << "\nFactura guardada en factura.txt\n";
}

// FUNCION PRINCIPAL

int main() {

    cout << fixed << setprecision(2);

    cout << "========================================\n";
    cout << "       SISTEMA DE RESTAURANTE\n";
    cout << "========================================\n";

    while (true) {

        int rol;

        // SELECCION DE ROL

        do {
            cout << "\n--- SELECCION DE ROL ---\n";
            cout << "1. Cliente\n";
            cout << "2. Empleado\n";
            cout << "3. Salir y generar reporte del dia\n";

            rol = leerEntero("Seleccione una opcion (1-3): ");

            if (rol < 1 || rol > 3) {
                cout << "Opcion invalida.\n";
            }

        } while (rol < 1 || rol > 3);

        if (rol == 3) {
            break;
        }

        string nombre;
        string empleadoActivo = "N/A";
        string tipoVenta = "cliente";

        // INGRESO DEL EMPLEADO

        if (rol == 2) {

            string usuario;

            cout << "Usuario de empleado: ";
            cin >> usuario;

            int pin = leerEntero("PIN de empleado: ");

            if (pin != PIN_EMPLEADO) {
                cout << "Credenciales incorrectas. Acceso denegado.\n";
                continue;
            }

            empleadoActivo = usuario;
            tipoVenta = "empleado";

            cout << "Sesion iniciada como: "
                 << empleadoActivo << endl;
        }

        // DATOS DEL CLIENTE

        limpiarEntrada();

        cout << "\nIngrese el nombre del cliente: ";
        getline(cin, nombre);

        int mesa = leerEntero("Ingrese el numero de mesa: ");

        cout << "\nBienvenido/a " << nombre
             << " a nuestro restaurante.\n";

        // CARRITO DE COMPRAS

        int itemsCarrito = 0;
        char otroProducto = 's';
        bool cancelarPedido = false;

        while (otroProducto == 's' || otroProducto == 'S') {

            mostrarMenu();
            mostrarCatalogo();

            int numProd = leerEntero(
                "\nSeleccione el numero del producto (1-20): "
            );

            if (numProd < 1 || numProd > NUM_PRODUCTOS) {
                cout << "Producto no existe. Intente nuevamente.\n";
                continue;
            }

            int idx = numProd - 1;

            int cant = leerEntero("Ingrese la cantidad deseada: ");

            if (cant <= 0 || cant > stock[idx]) {
                cout << "Stock insuficiente o cantidad invalida.\n";
                cout << "Disponible: " << stock[idx] << endl;
                continue;
            }

            if (itemsCarrito < MAX_CARRITO) {

                carritoProd[itemsCarrito] = idx;
                carritoCant[itemsCarrito] = cant;

                itemsCarrito++;

                stock[idx] -= cant;

                cout << "Producto agregado al carrito: "
                     << nombres[idx] << " x" << cant << endl;

            } else {
                cout << "Carrito lleno.\n";
                break;
            }

            cout << "\nDesea agregar otro producto? (s/n): ";
            cin >> otroProducto;
        }

        if (itemsCarrito == 0) {
            cout << "No hay productos en el carrito.\n";
            continue;
        }

        // CALCULO DEL SUBTOTAL

        double subtotal = 0;

        for (int i = 0; i < itemsCarrito; i++) {
            subtotal += precios[carritoProd[i]]
                        * carritoCant[i];
        }

        // DESCUENTOS

        char esEstudiante;

        cout << "\nEs estudiante universitario? (s/n): ";
        cin >> esEstudiante;

        double descEstudiante =
            (esEstudiante == 's' || esEstudiante == 'S')
            ? subtotal * 0.15 : 0.0;

        double baseDespuesEst = subtotal - descEstudiante;

        double descVolumen =
            (subtotal > 200.0)
            ? baseDespuesEst * 0.05 : 0.0;

        double baseGravable = baseDespuesEst - descVolumen;

        double iva = baseGravable * 0.13;

        double totalPagar = baseGravable + iva;

        // RESUMEN DEL PEDIDO

        cout << "\n========================================\n";
        cout << "          RESUMEN DEL PEDIDO\n";
        cout << "========================================\n";

        for (int i = 0; i < itemsCarrito; i++) {

            int idx = carritoProd[i];
            int cant = carritoCant[i];

            cout << nombres[idx] << " x" << cant
                 << " -> $" << precios[idx] * cant << endl;
        }

        cout << "----------------------------------------\n";
        cout << "Subtotal: $" << subtotal << endl;
        cout << "Descuento estudiante (15%): -$"
             << descEstudiante << endl;
        cout << "Descuento volumen (5%): -$"
             << descVolumen << endl;
        cout << "IVA (13%): +$" << iva << endl;
        cout << "TOTAL A PAGAR: $" << totalPagar << endl;

        // CONFIRMACION DEL PEDIDO

        char confirma;

        cout << "\nDesea confirmar su compra? (s/n): ";
        cin >> confirma;

        if (confirma != 's' && confirma != 'S') {

            for (int i = 0; i < itemsCarrito; i++) {
                stock[carritoProd[i]] += carritoCant[i];
            }

            cancelarPedido = true;

            cout << "Pedido cancelado. Stock restaurado.\n";
        }

        if (cancelarPedido) {
            continue;
        }

        // METODO DE PAGO

        int metodoPago;

        do {
            cout << "\n--- METODO DE PAGO ---\n";
            cout << "1. Efectivo\n";
            cout << "2. Tarjeta\n";

            metodoPago = leerEntero("Seleccione (1-2): ");

        } while (metodoPago != 1 && metodoPago != 2);

        double efectivo = 0;
        double cambio = 0;

        if (metodoPago == 1) {

            do {
                efectivo = leerDouble(
                    "Ingrese el monto recibido: $"
                );

                if (efectivo < totalPagar) {
                    cout << "Dinero insuficiente. Intente nuevamente.\n";
                }

            } while (efectivo < totalPagar);

            cambio = efectivo - totalPagar;

            cout << "Su cambio es: $" << cambio << endl;

        } else {
            cout << "Pago con tarjeta aprobado.\n";
        }

        // ACTUALIZAR VENTAS

        ventasTotalesDia += totalPagar;
        totalTransacciones++;

        for (int i = 0; i < itemsCarrito; i++) {
            unidadesVendidas[carritoProd[i]] += carritoCant[i];
        }

        // GENERAR FACTURA

        generarFactura(
            nombre,
            mesa,
            tipoVenta,
            empleadoActivo,
            itemsCarrito,
            subtotal,
            descEstudiante,
            descVolumen,
            iva,
            totalPagar,
            efectivo,
            cambio,
            metodoPago
        );

        // GUARDAR VENTA EN ARCHIVO

        ofstream archVentas("ventas.txt", ios::app);

        if (archVentas.is_open()) {

            archVentas << fixed << setprecision(2);

            archVentas << "Ticket #" << numeroTicket
                       << " | Cliente: " << nombre
                       << " | Mesa: " << mesa
                       << " | Tipo: " << tipoVenta
                       << " | Empleado: " << empleadoActivo
                       << " | Total: $" << totalPagar << endl;

            archVentas.close();
        }

        cout << "\nCompra realizada exitosamente.\n";
    }

    // REPORTE FINAL DEL DIA

    int idxEstrella = 0;

    for (int i = 1; i < NUM_PRODUCTOS; i++) {

        if (unidadesVendidas[i] > unidadesVendidas[idxEstrella]) {
            idxEstrella = i;
        }
    }

    string productoEstrella =
        (totalTransacciones > 0)
        ? nombres[idxEstrella] + " (" +
          to_string(unidadesVendidas[idxEstrella]) + " unidades)"
        : "Sin ventas registradas";

    ofstream archReporte("reporte_dia.txt");

    if (archReporte.is_open()) {

        archReporte << fixed << setprecision(2);

        archReporte << "====================================\n";
        archReporte << "         REPORTE DEL DIA\n";
        archReporte << "====================================\n";

        archReporte << "Total de transacciones: "
                    << totalTransacciones << endl;

        archReporte << "Ventas totales del dia: $"
                    << ventasTotalesDia << endl;

        archReporte << "Producto mas vendido: "
                    << productoEstrella << endl;

        archReporte.close();
    }

    cout << "\n========================================\n";
    cout << "           REPORTE DEL DIA\n";
    cout << "========================================\n";

    cout << "Transacciones: " << totalTransacciones << endl;
    cout << "Ventas totales: $" << ventasTotalesDia << endl;
    cout << "Producto estrella: " << productoEstrella << endl;

    cout << "\nReporte guardado en reporte_dia.txt\n";
    cout << "Ventas guardadas en ventas.txt\n";
    cout << "Facturas guardadas en factura.txt\n";

    cout << "\nGracias por visitar nuestro restaurante.\n";

    return 0;
}