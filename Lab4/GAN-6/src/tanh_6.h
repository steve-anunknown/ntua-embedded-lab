// Mapping tanh values from -2 to 1.984375 with a step of 0.015625

quantized_type tanh_vals[256] = { -0.9640275800758169, -0.9629068709757654, -0.9617519264982222, -0.9605617437853068, -0.9593352933146825, -0.958071518363745, -0.9567693344747047, -0.955427628921549, -0.9540452601799487, -0.9526210574012511, -0.9511538198917856, -0.9496423165987963, -0.9480852856044063, -0.9464814336291137, -0.94482943554642, -0.9431279339102947, -0.9413755384972874, -0.939570825865212, -0.937712338930443, -0.9357985865659837, -0.9338280432225917, -0.9317991485753769, -0.9297103071984134, -0.9275598882700505, -0.925346225311741, -0.9230676159633514, -0.92072232179806, -0.9183085681801013, -0.9158245441687624, -0.9132684024721864, -0.9106382594546996, -0.9079321952015192, -0.9051482536448664, -0.9022844427556502, -0.8993387348050462, -0.8963090667004403, -0.8931933404003516, -0.8899894234130917, -0.8866951493840524, -0.8833083187766378, -0.8798266996519848, -0.8762480285527146, -0.8725700114960693, -0.8687903250818614, -0.8649066177207418, -0.8609165109883439, -0.856817601110895, -0.852607460587903, -0.8482836399575129, -0.8438436697100982, -0.8392850623555859, -0.8346053146499223, -0.8298019099859595, -0.8248723209538826, -0.8198140120760964, -0.8146244427212479, -0.809301070201781, -0.80384135305908, -0.7982427545398869, -0.7925027462672406, -0.7866188121086977, -0.7805884522440585, -0.7744091874342136, -0.7680785634920665, -0.7615941559557649, -0.7549535749636815, -0.7481544703297354, -0.7411945368167219, -0.7340715196043415, -0.7267832199475612, -0.7193275010198336, -0.7117022939345188, -0.703905603936621, -0.6959355167556516, -0.6877902051090852, -0.6794679353444786, -0.6709670742068736, -0.6622860957166337, -0.6534235881413468, -0.6443782610439008, -0.6351489523872873, -0.6257346356751469, -0.6161344271055263, -0.606347592713803, -0.5963735554792423, -0.5862119023682238, -0.5758623912857893, -0.5653249579058751, -0.5545997223493823, -0.5436869956781494, -0.5325872861719194, -0.5213013053545766, -0.5098299737352566, -0.49817442622945507, -0.48633601722496234, -0.47431632525736667, -0.46211715726000974, -0.44974055235364957, -0.43718878514171233, -0.4244643684778938, -0.41157005567402244, -0.39850884211751697, -0.3852839662694723, -0.3718989100163851, -0.35835739835078595, -0.3446633983585721, -0.330821117493628, -0.316835001123366, -0.3027097293321085, -0.2884502129727393, -0.2740615889607664, -0.2595492148088268, -0.24491866240370913, -0.230175711032133, -0.21532633966578324, -0.20037671852040992, -0.1853331999081395, -0.17020230840646236, -0.1549907303716235, -0.13970530282831423, -0.12435300177159621, -0.10894092992085458, -0.09347630396922774, -0.07796644137536819, -0.062418746747512514, -0.04684069787264808, -0.031239831446031256, -0.015623728558408866, 0.0, 0.015623728558408866, 0.031239831446031256, 0.04684069787264808, 0.062418746747512514, 0.07796644137536819, 0.09347630396922774, 0.10894092992085458, 0.12435300177159621, 0.13970530282831423, 0.1549907303716235, 0.17020230840646236, 0.1853331999081395, 0.20037671852040992, 0.21532633966578324, 0.230175711032133, 0.24491866240370913, 0.2595492148088268, 0.2740615889607664, 0.2884502129727393, 0.3027097293321085, 0.316835001123366, 0.330821117493628, 0.3446633983585721, 0.35835739835078595, 0.3718989100163851, 0.3852839662694723, 0.39850884211751697, 0.41157005567402244, 0.4244643684778938, 0.43718878514171233, 0.44974055235364957, 0.46211715726000974, 0.47431632525736667, 0.48633601722496234, 0.49817442622945507, 0.5098299737352566, 0.5213013053545766, 0.5325872861719194, 0.5436869956781494, 0.5545997223493823, 0.5653249579058751, 0.5758623912857893, 0.5862119023682238, 0.5963735554792423, 0.606347592713803, 0.6161344271055263, 0.6257346356751469, 0.6351489523872873, 0.6443782610439008, 0.6534235881413468, 0.6622860957166337, 0.6709670742068736, 0.6794679353444786, 0.6877902051090852, 0.6959355167556516, 0.703905603936621, 0.7117022939345188, 0.7193275010198336, 0.7267832199475612, 0.7340715196043415, 0.7411945368167219, 0.7481544703297354, 0.7549535749636815, 0.7615941559557649, 0.7680785634920665, 0.7744091874342136, 0.7805884522440585, 0.7866188121086977, 0.7925027462672406, 0.7982427545398869, 0.80384135305908, 0.809301070201781, 0.8146244427212479, 0.8198140120760964, 0.8248723209538826, 0.8298019099859595, 0.8346053146499223, 0.8392850623555859, 0.8438436697100982, 0.8482836399575129, 0.852607460587903, 0.856817601110895, 0.8609165109883439, 0.8649066177207418, 0.8687903250818614, 0.8725700114960693, 0.8762480285527146, 0.8798266996519848, 0.8833083187766378, 0.8866951493840524, 0.8899894234130917, 0.8931933404003516, 0.8963090667004403, 0.8993387348050462, 0.9022844427556502, 0.9051482536448664, 0.9079321952015192, 0.9106382594546996, 0.9132684024721864, 0.9158245441687624, 0.9183085681801013, 0.92072232179806, 0.9230676159633514, 0.925346225311741, 0.9275598882700505, 0.9297103071984134, 0.9317991485753769, 0.9338280432225917, 0.9357985865659837, 0.937712338930443, 0.939570825865212, 0.9413755384972874, 0.9431279339102947, 0.94482943554642, 0.9464814336291137, 0.9480852856044063, 0.9496423165987963, 0.9511538198917856, 0.9526210574012511, 0.9540452601799487, 0.955427628921549, 0.9567693344747047, 0.958071518363745, 0.9593352933146825, 0.9605617437853068, 0.9617519264982222, 0.9629068709757654 };