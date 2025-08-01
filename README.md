radi samo na kali linuxu

Ovaj C++ program je **generator lozinki** s podrškom za izbjegavanje poznatih lozinki iz wordlista (`john.lst`, `wifite.txt`, `rockyou.txt`) i vođenjem evidencije o broju puta kada je svaka lozinka generirana. Evo detaljan opis njegovih funkcionalnosti:

---

### 🧠 **Funkcionalnosti:**

1. **Učitavanje prethodnih lozinki:**

   * Čita datoteku `passwords5.txt` i sprema lozinke i broj njihovih generiranja u `unordered_map`.

2. **Wordlist Blacklisting:**

   * Učitava jedan ili više wordlista (`john.lst`, `wifite.txt`, `rockyou.txt`) te ih koristi za **izbjegavanje poznatih lozinki**.
   * Sve lozinke iz wordlista sprema u `unordered_set` (blacklist).

3. **Generiranje lozinki:**

   * **Ručni unos duljine lozinke** (8-15 znakova).
   * Koristi predefinirani set znakova `CHARACTERS`.
   * Provjerava je li lozinka već korištena i koliko puta.

4. **Tri moda rada:**

   * `Opcija 1:` Ručno generiranje lozinke.
   * `Opcija 2:` Automatsko generiranje, uz provjeru protiv wordlista.
   * `Opcija 3:` Potpuno jedinstvena lozinka (nije generirana ranije i nije u wordlistama).

5. **Evidencija lozinki:**

   * Nakon svake lozinke ažurira i zapisuje stanje u `passwords5.txt`.

---

### 📁 **Datoteke i putanje:**

* `passwords5.txt`: Sprema generirane lozinke i broj njihovih ponavljanja.
* Wordlist datoteke:

  * `~/usr/share/wordlists/john.lst`
  * `~/usr/share/wordlists/wifite.txt`
  * `~/usr/share/wordlists/rockyou.txt`

> ⚠ Napomena: Putanja `~` se neće automatski proširiti. Preporučuje se koristiti punu putanju (`/home/korisnik/...`).

---

### 🔐 **Set znakova za generiranje:**

```cpp
abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@Ł!&#$/<>*ł?£&{}[]€;:-_÷^
```

> Uključuje velika/mala slova, brojeve i razne specijalne znakove (uključujući i Unicode znakove kao `Ł`, `€`, `ł`...).

---

### ✅ **Prednosti:**

* Povećana sigurnost izbjegavanjem poznatih lozinki.
* Jedinstveni mod koji osigurava potpunu originalnost lozinke.
* Dugoročno praćenje broja generiranja svake lozinke.

---

### 📌 **Moguće nadogradnje:**

* GUI verzija s Qt, GTK ili C++/CLI.
* Više opcija filtriranja (npr. isključi određene znakove).
* Šifriranje lozinki u datoteci.
* Bolja podrška za putanje (`~` expand).

---

Ako želiš, mogu ti pripremiti README.md za ovaj projekt, GUI verziju, ili konverziju u drugi jezik (npr. Java, Python, Kotlin).
