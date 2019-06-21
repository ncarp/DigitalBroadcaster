
CREATE VIEW [dbo].[ViewMusicTracks_OnAir]
AS
SELECT Broadcaster.dbo.MusicTracks.ID AS TrackID, 
    Broadcaster.dbo.MusicTracks.Title AS TrackTitle, 
    Broadcaster.dbo.Artists.Name AS ArtistName, 
    Broadcaster.dbo.MusicTracks.Finish - Broadcaster.dbo.MusicTracks.Start
     AS TrackLength, 
    Broadcaster.dbo.MusicTracks.Intro - Broadcaster.dbo.MusicTracks.Start
     AS TrackIntroTime, 
    Broadcaster.dbo.MusicTracks.Rythm AS TrackRythm, 
    Broadcaster.dbo.MusicTracks.LanguageID, 
    Broadcaster.dbo.MusicTracks.CategoryID, 
    Broadcaster.dbo.MusicTracks.ArtistID
FROM Broadcaster.dbo.MusicTracks INNER JOIN
    Broadcaster.dbo.Artists ON 
    Broadcaster.dbo.MusicTracks.ArtistID = Broadcaster.dbo.Artists.ID
WHERE (Broadcaster.dbo.MusicTracks.ID IN
        (SELECT MusicTrackID
      FROM ViewMusicTracksID_OnAir))

