# Proje Pusulası ile çalışma kuralı

Bu depo Proje Pusulası panelinde izlenir. Bu talimat, depoda çalışan yapay zekâ ajanları ve geliştiriciler içindir. Kullanıcının açık talimatları, güvenlik kuralları ve bu deponun daha özel talimatları önceliklidir.

## Çalışmaya başlarken
- README, mevcut proje belgeleri, açık issue ve PR'lar ile kökteki PROJECT_STATUS.md dosyasını incele. Mevcut işi ve kararları anlamadan yeni iş veya durum kaydı oluşturma.
- Kullanıcının istediği işi uygula; kapsamı yalnızca paneli doldurmak için genişletme.

## İş ilerlerken
- Yapılacak somut işleri GitHub issue ile takip et. Doğrulanmış hata, eksik, engel veya risk için `bug`, `hata`, `eksik`, `blocked`, `engel` ya da `risk` etiketi kullan. Planlanan hedef için `roadmap`, `hedef` veya `milestone` etiketi ya da açık milestone kullan. Etiket yoksa ve yetki varsa oluştur; yoksa PROJECT_STATUS.md içinde doğru başlık altında belirt.
- İnceleme veya birleştirme gerektiren değişiklikleri PR'da tut. Commit ve PR açıklamalarında ne değiştiğini, nedenini ve doğrulama sonucunu açıkça yaz.
- Yapılan işi test et veya uygun başka yolla doğrula. Doğrulanmayan bir sonucu tamamlandı diye sunma.

## Çalışma sonunda durum yayını
- Değişiklik, keşfedilen eksik veya plan değişikliği varsa PROJECT_STATUS.md dosyasını güncelle. Yalnızca gerçekten açık maddeleri `## Yapılacak`, `## Eksik`, `## Yol haritası` başlıkları altında `- [ ] Kısa, somut madde` biçiminde yaz. Biten maddeleri kaldır veya `[x]` yap.
- Aynı iş zaten açık issue veya milestone olarak kayıtlıysa durum dosyasında yineleme. Issue/PR durumunu ilerleme ve sonuçla güncelle; biten issue'yu kapat. Kararları ve gerekçeyi ilgili kayıtta kısa ve anlaşılır tut.
- Yayınlanan durum yalnızca GitHub'a gönderildiğinde panelde görünür. GitHub'a gönderme yetkisi yoksa yerel değişiklikleri hazırla ve kullanıcıya panelin henüz güncellenmediğini açıkça söyle.
- Hassas bilgi, token, kimlik bilgisi veya kişisel veri yayınlama. Bilinmeyen durumu tahmin ederek doldurma.

Proje Pusulası bu deponun README ve PROJECT_STATUS.md dosyalarını, açık issue/PR'ları, milestone'ları ve son commit'leri otomatik okur. Panelde elle kayıt girilmesi beklenmez.
