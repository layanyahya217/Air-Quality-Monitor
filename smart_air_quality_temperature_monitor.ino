// إعداد مستشعر TMP36
const int tempPin = A1; // المدخل المتصل بـ TMP36

// إعداد مستشعر الغاز
const int gasSensorPin = A0; // المدخل المتصل بـ MQ-2
const int gasThreshold = 300;//مستوى الغاز المرتفع
const float tempThreshold = 112.0; // درجة الحرارة التي تعتبر مرتفعة (بالدرجات المئوية)

// إعدادات LED وجهاز صفارة
const int ledPin1 = 2; 
const int ledPin2 = 4; 
const int buzzerPin = 7; 

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT); 
  pinMode(ledPin2, OUTPUT); 
  pinMode(buzzerPin, OUTPUT); 
}

void loop() {
  // قراءة درجة الحرارة من TMP36
  int tempReading = analogRead(tempPin); // قراءة القيمة
  float voltage = tempReading * (5.0 / 1023.0); // تحويل القيمة إلى فولت
  float temperature = (voltage - 0.5) * 100; // تحويل الفولت إلى درجة مئوية

  // قراءة مستوى الغاز
  int gasValue = analogRead(gasSensorPin);
  
  // عرض النتائج
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Gas Sensor Value: ");
  Serial.println(gasValue);
  
  // التحقق من درجة الحرارة
  if (temperature > tempThreshold) {
    Serial.println("Warning: High temperature detected!");
    digitalWrite(ledPin1, HIGH); // تشغيل LED 1
    tone(buzzerPin, 2000); // إصدار صوت تنبيه
  } else {
    Serial.println("Temperature is normal.");
    digitalWrite(ledPin1, LOW); // إيقاف تشغيل LED 1
    noTone(buzzerPin); // إيقاف الصفارة
  }

  // التحقق من مستوى الغاز
  if (gasValue > gasThreshold) {
    Serial.println("Warning: High gas level detected!");
    digitalWrite(ledPin2, HIGH); // تشغيل LED 2
    tone(buzzerPin, 1000); // إصدار صوت تنبيه
  } else {
    Serial.println("Gas level is normal.");
    digitalWrite(ledPin2, LOW); // إيقاف تشغيل LED 2
    noTone(buzzerPin); // إيقاف الصفارة
  }

  // إيقاف التنبيهات إذا كانت القيم ضمن المعدلات الطبيعية
  if (temperature <= tempThreshold && gasValue <= gasThreshold) {
    digitalWrite(ledPin1, LOW); // إيقاف تشغيل LED 1
    digitalWrite(ledPin2, LOW); // إيقاف تشغيل LED 2
    noTone(buzzerPin); // إيقاف الصفارة
  }

  delay(2000); // الانتظار لمدة ثانيتين
}

