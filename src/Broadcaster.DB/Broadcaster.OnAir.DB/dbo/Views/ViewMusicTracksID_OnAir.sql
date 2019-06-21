CREATE VIEW [dbo].[ViewMusicTracksID_OnAir]
AS
SELECT DISTINCT ID AS MusicTrackID
FROM         Broadcaster.dbo.MusicTracks
WHERE     (Activ <> 0) AND (NOT (ID IN
                          (SELECT     id
                            FROM          viewexcludedmusic))) OR
                      (Activ <> 0) AND (ID IN
                          (SELECT     id
                            FROM          viewListedmusic))
