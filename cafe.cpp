#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
using namespace std;

const int NUM_PRODUCTOS = 8;
const int MAX_CARRITO = 50;
const int PIN_EMPLEADO = 2007;

void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int leerEntero(const string& mensaje) {
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

double leerDouble(const string& mensaje) {
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

void mostrarCatalogo(const string nombres[], const double precios[], const int stock[]) {
    cout << "\n--- CATALOGO DE PRODUCTOS ---\n";
    for (int i = 0; i < NUM_PRODUCTOS; i++) {
        cout << (i + 1) << ". " << nombres[i]
             << " - $" << precios[i]
             << " (stock: " << stock[i] << ")\n";
    }
}

// Precios de comida
int main() {
    string nombres[NUM_PRODUCTOS] = {
        "Hamburguesa", "Tacos x 3", "Pizza", "Ensalada",
        "Cafe", "Jugo", "Postre", "Sandwich"
    };
    double precios[NUM_PRODUCTOS] = {4.00, 3.00, 5.00, 11.00, 2.00, 1.50, 4.50, 2.00};
    int stock[NUM_PRODUCTOS] = {20, 15, 10, 25, 50, 30, 12, 18};

    int carritoProd[MAX_CARRITO];
    int carritoCant[MAX_CARRITO];

    double ventasTotalesDia = 0.0;
    int totalTransacciones = 0;
    int unidadesVendidas[NUM_PRODUCTOS] = {0};
    int numeroTicket = 100;

    cout << fixed << setprecision(2);
    cout << "========================================\n";
    cout << "SISTEMA DE CAFETERIA UNIVERSITARIA\n";
    cout << "========================================\n";

    while (true) {
        int rol = 0;
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

        string empleadoActivo = "N/A";
        string tipoVenta = "cliente";

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
            cout << "Sesion iniciada como: " << empleadoActivo << "\n";
        }

        int itemsCarrito = 0;
        bool cancelarPedido = false;
        char otroProducto = 'n';

        do {
            mostrarCatalogo(nombres, precios, stock);
            int numProd = leerEntero("Numero de producto (1-8): ");
            if (numProd < 1 || numProd > NUM_PRODUCTOS) {
                cout << "Producto no existe. Rango valido: 1 a " << NUM_PRODUCTOS << ".\n";
                otroProducto = 's';
                continue;
            }

            int idx = numProd - 1;
            int cant = leerEntero("Cantidad deseada: ");
            if (cant <= 0 || cant > stock[idx]) {
                cout << "Stock insuficiente o cantidad invalida. Disponible: " << stock[idx] << ".\n";
                otroProducto = 's';
                continue;
            }

            if (itemsCarrito < MAX_CARRITO) {
                carritoProd[itemsCarrito] = idx;
                carritoCant[itemsCarrito] = cant;
                itemsCarrito++;
                stock[idx] -= cant;
                cout << "Agregado al carrito: " << nombres[idx] << " x" << cant << ".\n";
            } else {
                cout << "Carrito lleno.\n";
                break;
            }

            cout << "¿Agregar otro producto? (s/n): ";
            cin >> otroProducto;
        } while (otroProducto == 's' || otroProducto == 'S');

        if (itemsCarrito == 0) {
            cout << "No hay productos en el carrito.\n";
            continue;
        }

        double subtotal = 0.0;
        for (int i = 0; i < itemsCarrito; i++) {
            subtotal += precios[carritoProd[i]] * carritoCant[i];
        }

        char esEstudiante = 'n';
        cout << "¿Es estudiante universitario? (s/n): ";
        cin >> esEstudiante;

        double descEstudiante = (esEstudiante == 's' || esEstudiante == 'S') ? subtotal * 0.15 : 0.0;
        double baseDespuesEst = subtotal - descEstudiante;
        double descVolumen = (subtotal > 200.0) ? baseDespuesEst * 0.05 : 0.0;
        double baseGravable = baseDespuesEst - descVolumen;
        double iva = baseGravable * 0.13;
        double totalPagar = baseGravable + iva;

        cout << "\n--- RESUMEN DEL PEDIDO ---\n";
        for (int i = 0; i < itemsCarrito; i++) {
            int idx = carritoProd[i];
            int cant = carritoCant[i];
            cout << nombres[idx] << " x" << cant << " -> $" << (precios[idx] * cant) << "\n";
        }
        cout << "Subtotal:               $" << subtotal << "\n";
        cout << "Desc. estudiantil (15%): -$" << descEstudiante << "\n";
        cout << "Desc. volumen (> $200):  -$" << descVolumen << "\n";
        cout << "IVA (13%):              +$" << iva << "\n";
        cout << "TOTAL A PAGAR:          $" << totalPagar << "\n";

        char confirma = 'n';
        cout << "¿Confirmar compra? (s/n): ";
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

        int metodoPago = 0;
        do {
            cout << "\nMetodo de pago:\n1. Efectivo\n2. Tarjeta\n";
            metodoPago = leerEntero("Seleccione (1-2): ");
        } while (metodoPago != 1 && metodoPago != 2);

        double efectivo = 0.0, cambio = 0.0;
        if (metodoPago == 1) {
            do {
                efectivo = leerDouble("Monto recibido en efectivo: $");
                if (efectivo < totalPagar) {
                    cout << "Monto insuficiente.\n";
                }
            } while (efectivo < totalPagar);
            cambio = efectivo - totalPagar;
            cout << "Cambio: $" << cambio << "\n";
        } else {
            cout << "Pago con tarjeta aprobado.\n";
        }

        numeroTicket++;
        ventasTotalesDia += totalPagar;
        totalTransacciones++;
        for (int i = 0; i < itemsCarrito; i++) {
            unidadesVendidas[carritoProd[i]] += carritoCant[i];
        }

        ofstream archVentas("ventas.txt", ios::app);
        if (archVentas.is_open()) {
            archVentas << "Ticket #" << numeroTicket
                       << " | Tipo: " << tipoVenta
                       << " | Empleado: " << empleadoActivo
                       << " | Total: $" << totalPagar << "\n";
            archVentas.close();
        }

        cout << "\n========================================\n";
        cout << "COMPROBANTE - TICKET #" << numeroTicket << "\n";
        cout << "========================================\n";
        cout << "Tipo de venta: " << tipoVenta << " (" << empleadoActivo << ")\n";
        cout << "Total pagado: $" << totalPagar << "\n";
        cout << "========================================\n";
    }

    int idxEstrella = 0;
    for (int i = 1; i < NUM_PRODUCTOS; i++) {
        if (unidadesVendidas[i] > unidadesVendidas[idxEstrella]) {
            idxEstrella = i;
        }
    }

    string productoEstrella = (totalTransacciones > 0)
        ? (nombres[idxEstrella] + " (" + to_string(unidadesVendidas[idxEstrella]) + " unidades)")
        : "Sin ventas registradas";

    ofstream archReporte("reporte_dia.txt");
    if (archReporte.is_open()) {
        archReporte << "Total de transacciones: " << totalTransacciones << "\n";
        archReporte << "Ventas totales del dia: $" << ventasTotalesDia << "\n";
        archReporte << "Producto mas vendido: " << productoEstrella << "\n";
        archReporte.close();
    }

    cout << "\n--- REPORTE DEL DIA ---\n";
    cout << "Transacciones: " << totalTransacciones << "\n";
    cout << "Ventas totales: $" << ventasTotalesDia << "\n";
    cout << "Producto estrella: " << productoEstrella << "\n";
    cout << "Reporte guardado en reporte_dia.txt. ¡Hasta pronto!\n";

    return 0;
}