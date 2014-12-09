# all_data <-rbind(cbind(threshold_15, c(rep(15, 521)),
# cbind(threshold_30, rep(30, 521)),
# cbind(threshold_45, rep(45, 521)),
# cbind(threshold_60, rep(60, 521)),
# cbind(threshold_75, rep(75, 521)),
# cbind(threshold_90, rep(90, 521))))
# all_data <- cbind(rbind(threshold_15, threshold_30, threshold_45, threshold_60, threshold_75, threshold_90), th=c(rep(15,520), rep(30,520), rep(45,520), rep(60,520), rep(75,520), rep(90,520)))
# m_data <- melt(all_data, id=c("INDEX", "ADHD_SUBTYPE", "th"))
ADHD <-cbind(c(rep("com", 6), rep("int", 6), rep("hyp", 6), rep("typ", 6)),
  rbind(
  cbind(th=c(15,30,45,60,75,90), rbind(
colMeans(subset(ADHD_com, ADHD_com$th==15)[,15:22]),
colMeans(subset(ADHD_com, ADHD_com$th==30)[,15:22]),
colMeans(subset(ADHD_com, ADHD_com$th==45)[,15:22]), 
colMeans(subset(ADHD_com, ADHD_com$th==60)[,15:22]),
colMeans(subset(ADHD_com, ADHD_com$th==75)[,15:22]),
colMeans(subset(ADHD_com, ADHD_com$th==90)[,15:22])
)),
  cbind(th=c(15,30,45,60,75,90), rbind(
    colMeans(subset(ADHD_int, ADHD_int$th==15)[,15:22]),
    colMeans(subset(ADHD_int, ADHD_int$th==30)[,15:22]),
    colMeans(subset(ADHD_int, ADHD_int$th==45)[,15:22]), 
    colMeans(subset(ADHD_int, ADHD_int$th==60)[,15:22]),
    colMeans(subset(ADHD_int, ADHD_int$th==75)[,15:22]),
    colMeans(subset(ADHD_int, ADHD_int$th==90)[,15:22])
  )),
  cbind(th=c(15,30,45,60,75,90), rbind(
    colMeans(subset(ADHD_hyp, ADHD_hyp$th==15)[,15:22]),
    colMeans(subset(ADHD_hyp, ADHD_hyp$th==30)[,15:22]),
    colMeans(subset(ADHD_hyp, ADHD_hyp$th==45)[,15:22]), 
    colMeans(subset(ADHD_hyp, ADHD_hyp$th==60)[,15:22]),
    colMeans(subset(ADHD_hyp, ADHD_hyp$th==75)[,15:22]),
    colMeans(subset(ADHD_hyp, ADHD_hyp$th==90)[,15:22])
  )),
  cbind(th=c(15,30,45,60,75,90), rbind(
    colMeans(subset(ADHD_typ, ADHD_typ$th==15)[,15:22]),
    colMeans(subset(ADHD_typ, ADHD_typ$th==30)[,15:22]),
    colMeans(subset(ADHD_typ, ADHD_typ$th==45)[,15:22]), 
    colMeans(subset(ADHD_typ, ADHD_typ$th==60)[,15:22]),
    colMeans(subset(ADHD_typ, ADHD_typ$th==75)[,15:22]),
    colMeans(subset(ADHD_typ, ADHD_typ$th==90)[,15:22])
  ))
))   